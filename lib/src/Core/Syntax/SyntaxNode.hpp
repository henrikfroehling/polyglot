#ifndef POLYGLOT_CORE_SYNTAX_SYNTAXNODE_H
#define POLYGLOT_CORE_SYNTAX_SYNTAXNODE_H

#include "polyglot/Core/Syntax/ISyntaxNode.hpp"
#include "polyglot/Core/Syntax/ISyntaxTree.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Text/SourceText.hpp"
#include "polyglot/Core/Text/TextSpan.hpp"
#include "polyglot/Core/LanguageKind.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/SyntaxFlags.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxList;
class ISyntaxTrivia;
class ISyntaxTriviaList;

class SyntaxNode : public ISyntaxNode
{
public:
    explicit SyntaxNode(SyntaxKind syntaxKind,
                        pg_size position = 0,
                        pg_size fullWidth = 0,
                        ISyntaxNode* parent = nullptr,
                        ISyntaxTrivia* trivia = nullptr) noexcept;

    virtual ~SyntaxNode() noexcept {}

    SyntaxNode(const SyntaxNode&) noexcept = default;
    SyntaxNode(SyntaxNode&&) noexcept = default;
    SyntaxNode& operator=(const SyntaxNode&) noexcept = default;
    SyntaxNode& operator=(SyntaxNode&&) noexcept = default;

    inline ISyntaxNode* parent() const noexcept override final { return _pParent; }
    inline ISyntaxTrivia* trivia() const noexcept override final { return _pTrivia; }
    inline ISyntaxTree* syntaxTree() const noexcept override final { return _pSyntaxTree; }

    inline virtual LanguageKind languageKind() const noexcept override { return LanguageKind::Unknown; }
    inline SyntaxKind syntaxKind() const noexcept override final { return _syntaxKind; }
    virtual pg_string_view text() const noexcept override;
    virtual pg_string_view textIncludingTrivia() const noexcept override;

    inline virtual pg_size width() const noexcept override { return _fullWidth - leadingTriviaWidth() - trailingTriviaWidth(); }
    inline pg_size fullWidth() const noexcept override final { return _fullWidth; }
    inline pg_size position() const noexcept override final { return _position; }
    inline pg_size endPosition() const noexcept override final { return _position + width(); }
    inline pg_size positionIncludingTrivia() const noexcept override final { return _position - leadingTriviaWidth(); }
    inline pg_size endPositionIncludingTrivia() const noexcept override final { return positionIncludingTrivia() + _fullWidth; }
    inline virtual Text::TextSpan span() const noexcept override { return Text::TextSpan{_position, width()}; }
    inline virtual Text::TextSpan fullSpan() const noexcept override { return Text::TextSpan{positionIncludingTrivia(), _fullWidth}; }

    inline virtual pg_size childCount() const noexcept override { return 0; }
    inline virtual SyntaxVariant child(pg_size index) const override { return SyntaxVariant::empty(); }

    inline virtual SyntaxVariant first() const noexcept override { return SyntaxVariant::empty(); }
    inline virtual SyntaxVariant last() const noexcept override { return SyntaxVariant::empty(); }

    inline bool hasLeadingTrivia() const noexcept override final { return leadingTriviaWidth() != 0; }
    inline bool hasTrailingTrivia() const noexcept override final { return trailingTriviaWidth() != 0; }
    pg_size leadingTriviaWidth() const noexcept override final;
    pg_size trailingTriviaWidth() const noexcept override final;
    ISyntaxTriviaList* leadingTrivia() const noexcept override final;
    ISyntaxTriviaList* trailingTrivia() const noexcept override final;

    inline virtual bool isExpression() const noexcept override { return false; }
    inline virtual bool isStatement() const noexcept override { return false; }
    inline virtual bool isDeclaration() const noexcept override { return false; }
    inline virtual bool isClause() const noexcept override { return false; }
    bool hasMissingTokens() const noexcept override final;

    void setTriviaParent(ISyntaxTrivia* trivia) noexcept;
    void setSyntaxTree(ISyntaxTree* syntaxTree) noexcept;

    virtual pg_string toString() const noexcept override;
    virtual pg_string toShortString() const noexcept override;
    inline virtual pg_string typeName() const noexcept override { return L"SyntaxNode"; }

protected:
    void adjustWidthAndFlags(ISyntaxNode* node) noexcept;
    void adjustWidthAndFlags(ISyntaxToken* token) noexcept;
    void adjustWidthAndFlags(ISyntaxList* list) noexcept;

protected:
    friend class SyntaxList;

    pg_size _position;
    pg_size _fullWidth;
    SyntaxKind _syntaxKind;
    SyntaxFlags _flags;
    ISyntaxNode* _pParent;
    ISyntaxTrivia* _pTrivia;
    ISyntaxTree* _pSyntaxTree;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_SYNTAXNODE_H
