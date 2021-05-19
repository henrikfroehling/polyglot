#ifndef POLYGLOT_CORE_SYNTAX_TRIVIA_BRANCHINGDIRECTIVETRIVIASYNTAX_H
#define POLYGLOT_CORE_SYNTAX_TRIVIA_BRANCHINGDIRECTIVETRIVIASYNTAX_H

#include <string>
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

class BranchingDirectiveTriviaSyntax : public DirectiveTriviaSyntax
{
public:
    explicit BranchingDirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~BranchingDirectiveTriviaSyntax() noexcept {}
    virtual bool isBranchTaken() const noexcept = 0;

    virtual std::string typeName() const noexcept override { return "BranchingDirectiveTriviaSyntax"; }
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_TRIVIA_BRANCHINGDIRECTIVETRIVIASYNTAX_H
