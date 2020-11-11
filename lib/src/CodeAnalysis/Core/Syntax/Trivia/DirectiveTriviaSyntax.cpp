#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

DirectiveTriviaSyntax::DirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept
    : StructuredTriviaSyntax{syntaxKind}
{}

} // end namespace polyglot::CodeAnalysis
