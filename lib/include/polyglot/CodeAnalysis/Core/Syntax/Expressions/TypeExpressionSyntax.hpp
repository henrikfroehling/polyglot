#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TYPEEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TYPEEXPRESSIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API TypeExpressionSyntax : public ExpressionSyntax
{
public:
    explicit TypeExpressionSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~TypeExpressionSyntax() noexcept = default;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TYPEEXPRESSIONSYNTAX_H
