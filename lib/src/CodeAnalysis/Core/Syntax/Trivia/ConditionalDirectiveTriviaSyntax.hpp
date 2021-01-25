#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_CONDITIONALDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_CONDITIONALDIRECTIVETRIVIASYNTAX_H

#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/Trivia/BranchingDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
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

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_CONDITIONALDIRECTIVETRIVIASYNTAX_H
