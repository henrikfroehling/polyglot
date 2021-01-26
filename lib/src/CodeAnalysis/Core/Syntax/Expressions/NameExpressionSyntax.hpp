#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_NAMEEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_NAMEEXPRESSIONSYNTAX_H

#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Expressions/TypeExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class NameExpressionSyntax : public TypeExpressionSyntax
{
public:
    explicit NameExpressionSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~NameExpressionSyntax() noexcept = default;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_EXPRESSIONS_NAMEEXPRESSIONSYNTAX_H
