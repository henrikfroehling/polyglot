#include "CodeAnalysis/Core/Syntax/Trivia/BranchingDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

BranchingDirectiveTriviaSyntax::BranchingDirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept
    : DirectiveTriviaSyntax{syntaxKind}
{}

} // end namespace polyglot::CodeAnalysis
