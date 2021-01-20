#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ISYNTAXNODE_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ISYNTAXNODE_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/LanguageKind.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/SyntaxNodeFlags.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API ISyntaxNode
{
public:
    virtual ~ISyntaxNode() noexcept = default;

    virtual LanguageKind languageKind() const noexcept = 0;
    virtual SyntaxKind syntaxKind() const noexcept = 0;
    virtual SyntaxNodeFlags flags() const noexcept = 0;
    virtual pg_size width() const noexcept = 0;
    virtual pg_size fullWidth() const noexcept = 0;
    virtual pg_size childCount() const noexcept = 0;
    virtual ISyntaxNode* child(pg_size index) const noexcept = 0;
    virtual pg_size position() const noexcept = 0;
    virtual ISyntaxNode* parent() const noexcept = 0;
    virtual bool containsTrivia() const noexcept = 0;
    virtual bool containsStructuredTrivia() const noexcept = 0;
    virtual bool containsSkippedText() const noexcept = 0;
    virtual bool containsDirectives() const noexcept = 0;
    virtual bool isToken() const noexcept = 0;
    virtual bool isTrivia() const noexcept = 0;
    virtual bool isStructuredTrivia() const noexcept = 0;
    virtual bool isDirective() const noexcept = 0;
    virtual bool isSkippedTokensTrivia() const noexcept = 0;
    virtual bool isMissing() const noexcept = 0;
    virtual bool hasLeadingTrivia() const noexcept = 0;
    virtual bool hasTrailingTrivia() const noexcept = 0;
    virtual pg_size leadingTriviaWidth() const noexcept = 0;
    virtual pg_size trailingTriviaWidth() const noexcept = 0;
    virtual ISyntaxNode* leadingTriviaCore() const noexcept = 0;
    virtual ISyntaxNode* trailingTriviaCore() const noexcept = 0;

protected:
    ISyntaxNode() noexcept = default;
    ISyntaxNode(const ISyntaxNode&) noexcept = default;
    ISyntaxNode(ISyntaxNode&&) noexcept = default;
    ISyntaxNode& operator=(const ISyntaxNode&) noexcept = default;
    ISyntaxNode& operator=(ISyntaxNode&&) noexcept = default;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_ISYNTAXNODE_H
