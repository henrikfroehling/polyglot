#ifndef POLYGLOT_CORE_SYNTAX_SYNTAXLIST_H
#define POLYGLOT_CORE_SYNTAX_SYNTAXLIST_H

#include <string>
#include <vector>
#include "polyglot/Core/Syntax/ISyntaxList.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/SyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class ISyntaxTriviaList;

class SyntaxList : public ISyntaxList
{
public:
    explicit SyntaxList(SyntaxKind syntaxKind,
                        std::vector<SyntaxVariant>&& children,
                        pg_size position = 0,
                        pg_size fullWidth = 0,
                        ISyntaxNode* parent = nullptr) noexcept;

    virtual ~SyntaxList() noexcept {}

    SyntaxList(const SyntaxList&) noexcept = default;
    SyntaxList(SyntaxList&&) noexcept = default;
    SyntaxList& operator=(const SyntaxList&) noexcept = default;
    SyntaxList& operator=(SyntaxList&&) noexcept = default;

    inline ISyntaxNode* parent() const noexcept override final { return _pParent; }

    inline virtual LanguageKind languageKind() const noexcept override { return LanguageKind::Unknown; }
    inline SyntaxKind syntaxKind() const noexcept override final { return _syntaxKind; }
    virtual std::string_view text() const noexcept override;
    virtual std::string_view textIncludingTrivia() const noexcept override;

    inline virtual pg_size width() const noexcept override { return _fullWidth - leadingTriviaWidth() - trailingTriviaWidth(); }
    inline pg_size fullWidth() const noexcept override final { return _fullWidth; }
    inline pg_size position() const noexcept override final { return _position; }
    inline pg_size endPosition() const noexcept override final { return _position + width(); }
    inline pg_size positionIncludingTrivia() const noexcept override final { return _position - leadingTriviaWidth(); }
    inline pg_size endPositionIncludingTrivia() const noexcept override final { return positionIncludingTrivia() + _fullWidth; }
    inline virtual Text::TextSpan span() const noexcept override { return Text::TextSpan{_position, width()}; }
    inline virtual Text::TextSpan fullSpan() const noexcept override { return Text::TextSpan{positionIncludingTrivia(), _fullWidth}; }

    inline virtual pg_size childCount() const noexcept override { return _children.size(); }
    inline virtual SyntaxVariant child(pg_size index) const override { return _children[index]; }

    inline virtual SyntaxVariant first() const noexcept override { return _children.size() > 0 ? _children[0] : SyntaxVariant::empty(); }
    inline virtual SyntaxVariant last() const noexcept override { return _children.size() > 0 ? _children.back() : SyntaxVariant::empty(); }

    inline bool hasLeadingTrivia() const noexcept override final { return leadingTriviaWidth() != 0; }
    inline bool hasTrailingTrivia() const noexcept override final { return trailingTriviaWidth() != 0; }
    pg_size leadingTriviaWidth() const noexcept override final;
    pg_size trailingTriviaWidth() const noexcept override final;
    ISyntaxTriviaList* leadingTrivia() const noexcept override final;
    ISyntaxTriviaList* trailingTrivia() const noexcept override final;

    bool hasMissingTokens() const noexcept override final;

    std::string toString() const noexcept override;
    std::string toShortString() const noexcept override;

protected:
    void adjustWidthAndFlags(ISyntaxList* list) noexcept;
    void adjustWidthAndFlags(ISyntaxNode* node) noexcept;
    void adjustWidthAndFlags(ISyntaxToken* token) noexcept;
    void setParent(ISyntaxNode* parent) noexcept;

protected:
    friend class SyntaxNode;

    pg_size _position;
    pg_size _fullWidth;
    SyntaxKind _syntaxKind;
    ISyntaxNode* _pParent;
    std::vector<SyntaxVariant> _children;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_SYNTAXLIST_H
