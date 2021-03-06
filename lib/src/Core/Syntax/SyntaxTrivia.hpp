#ifndef POLYGLOT_CORE_SYNTAX_SYNTAXTRIVIA_H
#define POLYGLOT_CORE_SYNTAX_SYNTAXTRIVIA_H

#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/ISyntaxTrivia.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Text/TextSpan.hpp"
#include "polyglot/Core/LanguageKind.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Parser/DirectiveStack.hpp"

namespace polyglot::Core::Syntax
{

class SyntaxTrivia : public ISyntaxTrivia
{
public:
    explicit SyntaxTrivia(SyntaxKind syntaxKind,
                          pg_string_view text,
                          pg_size position = 0,
                          pg_size width = 0,
                          ISyntaxToken* token = nullptr) noexcept;

    virtual ~SyntaxTrivia() noexcept {}

    SyntaxTrivia(const SyntaxTrivia&) noexcept = default;
    SyntaxTrivia(SyntaxTrivia&&) noexcept = default;
    SyntaxTrivia& operator=(const SyntaxTrivia&) noexcept = default;
    SyntaxTrivia& operator=(SyntaxTrivia&&) noexcept = default;

    inline ISyntaxToken* token() const noexcept override final { return _pToken; }

    inline LanguageKind languageKind() const noexcept override final { return _pToken != nullptr ? _pToken->languageKind() : LanguageKind::Unknown; }
    inline SyntaxKind syntaxKind() const noexcept override final { return _syntaxKind; }
    inline pg_string_view text() const noexcept override final { return _text; }

    inline pg_size width() const noexcept override final { return _width; }
    inline pg_size position() const noexcept override final { return _position; }
    inline pg_size endPosition() const noexcept override final { return _position + _width; }
    inline Text::TextSpan span() const noexcept override final { return Text::TextSpan{_position, width()}; }

    inline virtual bool isStructuredTrivia() const noexcept override { return false; }
    inline virtual bool isDirective() const noexcept override { return false; }
    inline virtual bool isSkippedTokensTrivia() const noexcept override { return false; }
    inline virtual bool isWhitespace() const noexcept override { return false; }
    inline virtual bool isComment() const noexcept override { return false; }
    inline virtual bool isLineEnding() const noexcept override { return false; }
    inline bool isLeading() const noexcept override final { return _isLeading; }
    inline bool isTrailing() const noexcept override final { return _isTrailing; }

    inline virtual Parser::DirectiveStack applyDirectives(Parser::DirectiveStack stack) const noexcept { return std::move(stack); }

    pg_string toString() const noexcept override;
    pg_string toShortString() const noexcept override;
    inline virtual pg_string typeName() const noexcept override { return L"SyntaxTrivia"; }

protected:
    friend class SyntaxToken;
    friend class SyntaxTriviaList;

    pg_size _position;
    pg_size _width;
    SyntaxKind _syntaxKind;
    pg_string_view _text;
    ISyntaxToken* _pToken;
    bool _isLeading;
    bool _isTrailing;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_SYNTAXTRIVIA_H
