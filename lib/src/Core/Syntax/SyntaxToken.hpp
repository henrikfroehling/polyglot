#ifndef POLYGLOT_CORE_SYNTAX_SYNTAXTOKEN_H
#define POLYGLOT_CORE_SYNTAX_SYNTAXTOKEN_H

#include <string_view>
#include "polyglot/Core/Syntax/ISyntaxNode.hpp"
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/ISyntaxTriviaList.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Text/TextSpan.hpp"
#include "polyglot/Core/LanguageKind.hpp"
#include "polyglot/Core/Types.hpp"
#include "SyntaxFlags.hpp"

namespace polyglot::Core::Syntax
{

class SyntaxToken : public ISyntaxToken
{
public:
    SyntaxToken() noexcept;

    explicit SyntaxToken(SyntaxKind syntaxKind,
                         std::string_view text,
                         pg_size position = 0,
                         pg_size fullWidth = 0,
                         ISyntaxTriviaList* leadingTrivia = nullptr,
                         ISyntaxTriviaList* trailingTrivia = nullptr,
                         ISyntaxNode* parent = nullptr) noexcept;

    virtual ~SyntaxToken() noexcept {}

    SyntaxToken(const SyntaxToken&) noexcept = default;
    SyntaxToken(SyntaxToken&&) noexcept = default;
    SyntaxToken& operator=(const SyntaxToken&) noexcept = default;
    SyntaxToken& operator=(SyntaxToken&&) noexcept = default;

    inline ISyntaxNode* parent() const noexcept override final { return _pParent; }

    inline LanguageKind languageKind() const noexcept override final { return _pParent != nullptr ? _pParent->languageKind() : LanguageKind::Unknown; }
    inline SyntaxKind syntaxKind() const noexcept override final { return _syntaxKind; }
    inline std::string_view text() const noexcept override final { return _text; }
    inline std::string_view textIncludingTrivia() const noexcept override final { return std::string_view{}; }

    inline pg_size width() const noexcept override final { return _fullWidth - leadingTriviaWidth() - trailingTriviaWidth(); }
    inline pg_size fullWidth() const noexcept override final { return _fullWidth; }
    inline pg_size position() const noexcept override final { return _position; }
    inline pg_size endPosition() const noexcept override final { return _position + width(); }
    inline pg_size positionIncludingTrivia() const noexcept override final { return _position - leadingTriviaWidth(); }
    inline pg_size endPositionIncludingTrivia() const noexcept override final { return positionIncludingTrivia() + _fullWidth; }
    inline Text::TextSpan span() const noexcept override final { return Text::TextSpan{_position, width()}; }
    inline Text::TextSpan fullSpan() const noexcept override final { return Text::TextSpan{endPositionIncludingTrivia(), _fullWidth}; }

    inline bool hasLeadingTrivia() const noexcept override final { return _pLeadingTrivia != nullptr && _pLeadingTrivia->count() > 0; }
    inline bool hasTrailingTrivia() const noexcept override final { return _pTrailingTrivia != nullptr && _pTrailingTrivia->count() > 0; }
    inline pg_size leadingTriviaWidth() const noexcept override final { return _pLeadingTrivia != nullptr ? _pLeadingTrivia->width() : 0; }
    inline pg_size trailingTriviaWidth() const noexcept override final { return _pTrailingTrivia != nullptr ? _pTrailingTrivia->width() : 0; }
    inline ISyntaxTriviaList* leadingTrivia() const noexcept override final { return _pLeadingTrivia; }
    inline ISyntaxTriviaList* trailingTrivia() const noexcept override final { return _pTrailingTrivia; }

    inline virtual bool isKeyword() const noexcept override { return false; }
    inline virtual bool isIdentifier() const noexcept override { return false; }
    inline virtual bool isLiteral() const noexcept override { return false; }
    inline virtual bool isPunctuation() const noexcept override { return false; }
    inline bool isMissing() const noexcept override final { return (_flags & SyntaxFlags::IsMssing) != SyntaxFlags::None; }

    TokenValue value() const noexcept override;
    bool booleanValue() const noexcept override;

protected:
    void adjustWidth(ISyntaxTriviaList* trivia) noexcept;

protected:
    pg_size _position;
    pg_size _fullWidth;
    SyntaxKind _syntaxKind;
    SyntaxFlags _flags;
    ISyntaxNode* _pParent;
    std::string_view _text;
    ISyntaxTriviaList* _pLeadingTrivia;
    ISyntaxTriviaList* _pTrailingTrivia;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_SYNTAXTOKEN_H
