#include "Core/Syntax/Trivia/UndefDirectiveTriviaSyntax.hpp"

namespace polyglot::Core::Syntax
{

UndefDirectiveTriviaSyntax::UndefDirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept
    : DirectiveTriviaSyntax{syntaxKind}
{}

} // end namespace polyglot::Core::Syntax
