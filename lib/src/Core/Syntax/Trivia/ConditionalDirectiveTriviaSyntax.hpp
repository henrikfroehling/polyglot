#ifndef POLYGLOT_CORE_SYNTAX_TRIVIA_CONDITIONALDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CORE_SYNTAX_TRIVIA_CONDITIONALDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "BranchingDirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ExpressionSyntax;

class ConditionalDirectiveTriviaSyntax : public BranchingDirectiveTriviaSyntax
{
public:
    explicit ConditionalDirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~ConditionalDirectiveTriviaSyntax() noexcept = default;
    virtual ExpressionSyntax* condition() const noexcept = 0;
    virtual bool conditionValue() const noexcept = 0;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_TRIVIA_CONDITIONALDIRECTIVETRIVIASYNTAX_H
