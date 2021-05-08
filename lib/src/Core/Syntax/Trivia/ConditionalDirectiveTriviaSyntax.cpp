#include "ConditionalDirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

ConditionalDirectiveTriviaSyntax::ConditionalDirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept
    : BranchingDirectiveTriviaSyntax{syntaxKind}
{}

} // end namespace polyglot::Core::Syntax
