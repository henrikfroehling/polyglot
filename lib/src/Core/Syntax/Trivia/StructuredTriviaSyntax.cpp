#include "Core/Syntax/Trivia/StructuredTriviaSyntax.hpp"
#include "polyglot/Core/Syntax/ISyntaxNode.hpp"
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"

namespace polyglot::Core::Syntax
{

StructuredTriviaSyntax::StructuredTriviaSyntax(SyntaxKind syntaxKind) noexcept
    : SyntaxTrivia{syntaxKind, L""}
{}

void StructuredTriviaSyntax::adjustWidth(ISyntaxNode* node) noexcept
{
    if (node != nullptr)
        _width += node->fullWidth();
}

void StructuredTriviaSyntax::adjustWidth(ISyntaxToken* token) noexcept
{
    if (token != nullptr)
        _width += token->fullWidth();
}

} // end namespace polyglot::Core::Syntax
