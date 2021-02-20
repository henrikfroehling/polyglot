#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODE_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODE_H

#include <vector>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/LanguageKind.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Text/TextSpan.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxNodeFlags.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxToken;
class ISyntaxTriviaList;

class SyntaxNode : public virtual ISyntaxNode
{
public:
    SyntaxNode() noexcept;

    explicit SyntaxNode(SyntaxKind syntaxKind,
                        pg_size position = 0,
                        pg_size fullWidth = 0,
                        ISyntaxNode* parent = nullptr) noexcept;

    virtual ~SyntaxNode() noexcept;

    SyntaxNode(const SyntaxNode&) noexcept = default;
    SyntaxNode(SyntaxNode&&) noexcept = default;
    SyntaxNode& operator=(const SyntaxNode&) noexcept = default;
    SyntaxNode& operator=(SyntaxNode&&) noexcept = default;

    inline virtual LanguageKind languageKind() const noexcept override { return LanguageKind::Unknown; }
    inline SyntaxKind syntaxKind() const noexcept override final { return _syntaxKind; }
    inline SyntaxNodeFlags flags() const noexcept { return _flags; }
    inline virtual pg_size width() const noexcept override { return _fullWidth - leadingTriviaWidth() - trailingTriviaWidth(); }
    inline pg_size fullWidth() const noexcept override final { return _fullWidth; }
    inline virtual pg_size childCount() const noexcept override { return 0; }
    inline virtual ISyntaxNode* child(pg_size index) const override { return nullptr; }
    inline pg_size position() const noexcept override final { return _position; }
    inline pg_size endPosition() const noexcept override final { return _position + width() + trailingTriviaWidth(); }
    inline pg_size spanStart() const noexcept override final { return _position; }
    inline virtual TextSpan span() const noexcept override { return TextSpan{_position, width()}; }
    inline virtual TextSpan fullSpan() const noexcept override { return TextSpan{_position - leadingTriviaWidth(), _fullWidth}; }
    inline virtual std::string_view text() const noexcept override { return ""; }
    inline ISyntaxNode* parent() const noexcept override final { return _pParent; }

    inline bool containsTrivia() const noexcept override final { return (_flags & SyntaxNodeFlags::ContainsTrivia) != SyntaxNodeFlags::None; }
    inline bool containsStructuredTrivia() const noexcept override final { return (_flags & SyntaxNodeFlags::ContainsStructuredTrivia) != SyntaxNodeFlags::None; }
    inline bool containsSkippedText() const noexcept override final { return (_flags & SyntaxNodeFlags::ContainsSkippedText) != SyntaxNodeFlags::None; }
    inline bool containsDirectives() const noexcept override final { return (_flags & SyntaxNodeFlags::ContainsDirectives) != SyntaxNodeFlags::None; }
    inline virtual bool isToken() const noexcept override { return false; }
    inline virtual bool isTrivia() const noexcept override { return false; }
    inline virtual bool isStructuredTrivia() const noexcept override { return false; }
    inline virtual bool isDirective() const noexcept override { return false; }
    inline virtual bool isSkippedTokensTrivia() const noexcept override { return false; }
    inline virtual bool isExpression() const noexcept override { return false; }
    inline bool isMissing() const noexcept override final { return (_flags & SyntaxNodeFlags::IsMissing) != SyntaxNodeFlags::None; }
    virtual bool hasMissingTokens() const noexcept override;

    inline virtual bool hasLeadingTrivia() const noexcept override { return leadingTriviaWidth() != 0; }
    inline virtual bool hasTrailingTrivia() const noexcept override { return trailingTriviaWidth() != 0; }
    virtual pg_size leadingTriviaWidth() const noexcept override;
    virtual pg_size trailingTriviaWidth() const noexcept override;
    inline virtual ISyntaxTriviaList* leadingTrivia() const noexcept override { return nullptr; }
    inline virtual ISyntaxTriviaList* trailingTrivia() const noexcept override { return nullptr; }

    ISyntaxToken* firstToken() const noexcept;
    ISyntaxToken* lastToken() const noexcept;

protected:
    void adjustWidthAndFlags(ISyntaxNode* node) noexcept;

protected:
    pg_size _position;
    pg_size _fullWidth;
    SyntaxKind _syntaxKind;
    SyntaxNodeFlags _flags;
    ISyntaxNode* _pParent;

private:
    ISyntaxNode* firstTerminal() const noexcept;
    ISyntaxNode* lastTerminal() const noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODE_H
