#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_CONDITIONALDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_CONDITIONALDIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/BranchingDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class ExpressionSyntax;

class POLYGLOT_API ConditionalDirectiveTriviaSyntax : public BranchingDirectiveTriviaSyntax
{
public:
    explicit ConditionalDirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~ConditionalDirectiveTriviaSyntax() noexcept = default;
    virtual ExpressionSyntax* condition() const noexcept = 0;
    virtual bool conditionValue() const noexcept = 0;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_CONDITIONALDIRECTIVETRIVIASYNTAX_H
