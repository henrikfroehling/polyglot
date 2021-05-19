#ifndef POLYGLOT_CORE_SYNTAX_EXPRESSIONSYNTAX_H
#define POLYGLOT_CORE_SYNTAX_EXPRESSIONSYNTAX_H

#include <string>
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class ExpressionSyntax : public SyntaxNode
{
public:
    explicit ExpressionSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~ExpressionSyntax() noexcept {}
    inline bool isExpression() const noexcept override { return true; }

    virtual std::string typeName() const noexcept override { return "ExpressionSyntax"; }
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_EXPRESSIONSYNTAX_H
