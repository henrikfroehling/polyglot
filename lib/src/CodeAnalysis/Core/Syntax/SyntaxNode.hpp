#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODE_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODE_H

#include <vector>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/LanguageKind.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Text/TextSpan.hpp"
#include "CodeAnalysis/Core/SyntaxNodeFlags.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxNode final : public ISyntaxNode
{
public:
    SyntaxNode() noexcept;

    explicit SyntaxNode(LanguageSyntaxNode* underlyingNode,
                        ISyntaxNode* parent = nullptr) noexcept;

    virtual ~SyntaxNode() noexcept;

    SyntaxNode(const SyntaxNode&) noexcept = default;
    SyntaxNode(SyntaxNode&&) noexcept = default;
    SyntaxNode& operator=(const SyntaxNode&) noexcept = default;
    SyntaxNode& operator=(SyntaxNode&&) noexcept = default;

    inline LanguageKind languageKind() const noexcept override { return _pUnderlyingNode->languageKind(); }
    inline SyntaxKind syntaxKind() const noexcept override { return _pUnderlyingNode->syntaxKind(); }
    inline SyntaxNodeFlags flags() const noexcept { return _pUnderlyingNode->flags(); }
    inline pg_size width() const noexcept override { return _pUnderlyingNode->width(); }
    inline pg_size fullWidth() const noexcept override { return _pUnderlyingNode->fullWidth(); }
    inline pg_size childCount() const noexcept override { return _pUnderlyingNode->childCount(); }
    inline pg_size position() const noexcept override { return _pUnderlyingNode->position(); }
    inline pg_size endPosition() const noexcept override { return _pUnderlyingNode->endPosition(); }
    inline pg_size spanStart() const noexcept { return _pUnderlyingNode->spanStart(); }
    TextSpan span() const noexcept;
    inline TextSpan fullSpan() const noexcept { return _pUnderlyingNode->fullSpan(); }
    inline ISyntaxNode* parent() const noexcept override { return _pParent; }

    inline bool containsTrivia() const noexcept override { return _pUnderlyingNode->containsTrivia(); }
    inline bool containsStructuredTrivia() const noexcept override { return _pUnderlyingNode->containsStructuredTrivia(); }
    inline bool containsSkippedText() const noexcept override { return _pUnderlyingNode->containsSkippedText(); }
    inline bool containsDirectives() const noexcept override { return _pUnderlyingNode->containsDirectives(); }
    inline bool isMissing() const noexcept override { return _pUnderlyingNode->isMissing(); }

    inline bool hasLeadingTrivia() const noexcept override { return _pUnderlyingNode->hasLeadingTrivia(); }
    inline bool hasTrailingTrivia() const noexcept override { return _pUnderlyingNode->hasTrailingTrivia(); }
    inline std::vector<ISyntaxTrivia*> leadingTrivia() const noexcept override { return std::vector<ISyntaxTrivia*>{}; }
    inline std::vector<ISyntaxTrivia*> trailingTrivia() const noexcept override { return std::vector<ISyntaxTrivia*>{}; }
    inline pg_size leadingTriviaWidth() const noexcept { return _pUnderlyingNode->leadingTriviaWidth(); }
    inline pg_size trailingTriviaWidth() const noexcept { return _pUnderlyingNode->trailingTriviaWidth(); }

protected:
    LanguageSyntaxNode* _pUnderlyingNode;
    ISyntaxNode* _pParent;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_SYNTAXNODE_H
