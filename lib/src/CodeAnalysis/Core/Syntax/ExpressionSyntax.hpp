#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONSYNTAX_H

#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class ExpressionSyntax : public SyntaxNode
{
public:
    explicit ExpressionSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~ExpressionSyntax() noexcept = default;
    inline bool isExpression() const noexcept override { return true; }
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONSYNTAX_H
