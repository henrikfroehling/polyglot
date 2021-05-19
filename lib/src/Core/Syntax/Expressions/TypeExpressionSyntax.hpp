#ifndef POLYGLOT_CORE_SYNTAX_EXPRESSIONS_TYPEEXPRESSIONSYNTAX_H
#define POLYGLOT_CORE_SYNTAX_EXPRESSIONS_TYPEEXPRESSIONSYNTAX_H

#include <string>
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::Core::Syntax
{

class TypeExpressionSyntax : public ExpressionSyntax
{
public:
    explicit TypeExpressionSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~TypeExpressionSyntax() noexcept {}

    virtual std::string typeName() const noexcept override { return "TypeExpressionSyntax"; }
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_EXPRESSIONS_TYPEEXPRESSIONSYNTAX_H
