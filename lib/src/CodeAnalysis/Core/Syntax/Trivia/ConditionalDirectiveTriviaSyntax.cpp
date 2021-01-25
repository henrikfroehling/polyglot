#include "CodeAnalysis/Core/Syntax/Trivia/ConditionalDirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

ConditionalDirectiveTriviaSyntax::ConditionalDirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept
    : BranchingDirectiveTriviaSyntax{syntaxKind}
{}

} // end namespace polyglot::CodeAnalysis
