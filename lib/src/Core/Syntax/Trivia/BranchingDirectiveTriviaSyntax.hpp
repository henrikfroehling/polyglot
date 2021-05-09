#ifndef POLYGLOT_CORE_SYNTAX_TRIVIA_BRANCHINGDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CORE_SYNTAX_TRIVIA_BRANCHINGDIRECTIVETRIVIASYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "DirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class BranchingDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit BranchingDirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~BranchingDirectiveTriviaSyntax() noexcept {}
    virtual bool isBranchTaken() const noexcept = 0;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_TRIVIA_BRANCHINGDIRECTIVETRIVIASYNTAX_H
