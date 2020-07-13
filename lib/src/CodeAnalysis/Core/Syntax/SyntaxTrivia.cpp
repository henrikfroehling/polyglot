#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxTrivia::SyntaxTrivia() noexcept
    : SyntaxNode{},
      _text{}
{}

SyntaxTrivia::SyntaxTrivia(SyntaxKind syntaxKind,
                           std::string_view text) noexcept
    : SyntaxNode{syntaxKind},
      _text{std::move(text)}
{}

SyntaxTrivia::~SyntaxTrivia() noexcept
{}

} // end namespace polyglot::CodeAnalysis
