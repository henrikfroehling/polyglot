#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_CONDITIONALDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_CONDITIONALDIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/BranchingDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API ConditionalDirectiveTriviaSyntax : public BranchingDirectiveTriviaSyntax
{
public:
    explicit ConditionalDirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~ConditionalDirectiveTriviaSyntax() noexcept = default;
    virtual const Ptr<ExpressionSyntax> condition() const noexcept = 0;
    virtual bool conditionValue() const noexcept = 0;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_CONDITIONALDIRECTIVETRIVIASYNTAX_H
