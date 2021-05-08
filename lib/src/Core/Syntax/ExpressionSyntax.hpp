#ifndef POLYGLOT_CORE_SYNTAX_EXPRESSIONSYNTAX_H
#define POLYGLOT_CORE_SYNTAX_EXPRESSIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "SyntaxNode.hpp"

namespace polyglot::Core::Syntax
{

class ExpressionSyntax : public SyntaxNode
{
public:
    explicit ExpressionSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~ExpressionSyntax() noexcept = default;
    inline bool isExpression() const noexcept override { return true; }
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_EXPRESSIONSYNTAX_H
