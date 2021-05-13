#ifndef POLYGLOT_CORE_SYNTAX_EXPRESSIONS_TYPEEXPRESSIONSYNTAX_H
#define POLYGLOT_CORE_SYNTAX_EXPRESSIONS_TYPEEXPRESSIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::Core::Syntax
{

class TypeExpressionSyntax : public ExpressionSyntax
{
public:
    explicit TypeExpressionSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~TypeExpressionSyntax() noexcept {}
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_EXPRESSIONS_TYPEEXPRESSIONSYNTAX_H
