#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxTrivia::SyntaxTrivia(SyntaxKind syntaxKind,
                           std::string_view text) noexcept
    : SyntaxNode{syntaxKind},
      _text{std::move(text)}
{}

} // end namespace polyglot::CodeAnalysis
