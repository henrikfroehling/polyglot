#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNodeFlags.hpp"

namespace polyglot::CodeAnalysis
{

DirectiveTriviaSyntax::DirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept
    : StructuredTriviaSyntax{syntaxKind}
{}

} // end namespace polyglot::CodeAnalysis
