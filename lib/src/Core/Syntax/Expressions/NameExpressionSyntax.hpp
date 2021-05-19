#ifndef POLYGLOT_CORE_SYNTAX_EXPRESSIONS_NAMEEXPRESSIONSYNTAX_H
#define POLYGLOT_CORE_SYNTAX_EXPRESSIONS_NAMEEXPRESSIONSYNTAX_H

#include <string>
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/Expressions/TypeExpressionSyntax.hpp"

namespace polyglot::Core::Syntax
{

class NameExpressionSyntax : public TypeExpressionSyntax
{
public:
    explicit NameExpressionSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~NameExpressionSyntax() noexcept {}

    virtual std::string typeName() const noexcept override { return "NameExpressionSyntax"; }
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_EXPRESSIONS_NAMEEXPRESSIONSYNTAX_H
