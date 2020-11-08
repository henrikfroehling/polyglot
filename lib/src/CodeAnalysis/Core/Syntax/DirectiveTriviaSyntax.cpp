#include "polyglot/CodeAnalysis/Core/Syntax/DirectiveTriviaSyntax.hpp"

namespace polyglot::CodeAnalysis
{

DirectiveTriviaSyntax::DirectiveTriviaSyntax(SyntaxKind syntaxKind) noexcept
    : StructuredTriviaSyntax{syntaxKind}
{}

} // end namespace polyglot::CodeAnalysis
