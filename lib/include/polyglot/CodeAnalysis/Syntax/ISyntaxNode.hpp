#ifndef POLYGLOT_CODEANALYSIS_SYNTAX_ISYNTAXNODE_H
#define POLYGLOT_CODEANALYSIS_SYNTAX_ISYNTAXNODE_H

#include <vector>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/LanguageKind.hpp"
#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Text/TextSpan.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxTrivia;

class POLYGLOT_API ISyntaxNode
{
public:
    virtual ~ISyntaxNode() noexcept = default;

    virtual LanguageKind languageKind() const noexcept = 0;
    virtual SyntaxKind syntaxKind() const noexcept = 0;
    virtual pg_size width() const noexcept = 0;
    virtual pg_size fullWidth() const noexcept = 0;
    virtual pg_size childCount() const noexcept = 0;
    virtual pg_size position() const noexcept = 0;
    virtual pg_size endPosition() const noexcept = 0;
    virtual pg_size spanStart() const noexcept = 0;
    virtual TextSpan span() const noexcept = 0;
    virtual TextSpan fullSpan() const noexcept = 0;
    virtual ISyntaxNode* parent() const noexcept = 0;

    virtual bool containsTrivia() const noexcept = 0;
    virtual bool containsStructuredTrivia() const noexcept = 0;
    virtual bool containsSkippedText() const noexcept = 0;
    virtual bool containsDirectives() const noexcept = 0;
    virtual bool isMissing() const noexcept = 0;

    virtual bool hasLeadingTrivia() const noexcept = 0;
    virtual bool hasTrailingTrivia() const noexcept = 0;
    virtual std::vector<ISyntaxTrivia*> leadingTrivia() const noexcept = 0;
    virtual std::vector<ISyntaxTrivia*> trailingTrivia() const noexcept = 0;

protected:
    ISyntaxNode() noexcept = default;
    ISyntaxNode(const ISyntaxNode&) noexcept = default;
    ISyntaxNode(ISyntaxNode&&) noexcept = default;
    ISyntaxNode& operator=(const ISyntaxNode&) noexcept = default;
    ISyntaxNode& operator=(ISyntaxNode&&) noexcept = default;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_SYNTAX_ISYNTAXNODE_H
