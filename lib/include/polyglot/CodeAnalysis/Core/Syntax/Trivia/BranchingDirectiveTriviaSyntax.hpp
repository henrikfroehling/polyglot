#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_BRANCHINGDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_BRANCHINGDIRECTIVETRIVIASYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API BranchingDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit BranchingDirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~BranchingDirectiveTriviaSyntax() noexcept = default;
    virtual bool isBranchTaken() const noexcept = 0;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAX_TRIVIA_BRANCHINGDIRECTIVETRIVIASYNTAX_H
