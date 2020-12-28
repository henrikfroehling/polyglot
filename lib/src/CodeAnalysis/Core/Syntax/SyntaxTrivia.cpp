#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxTrivia::SyntaxTrivia() noexcept
    : SyntaxNode{},
      _text{}
{}

SyntaxTrivia::SyntaxTrivia(SyntaxKind syntaxKind) noexcept
    : SyntaxNode{syntaxKind},
      _text{}
{}

SyntaxTrivia::SyntaxTrivia(SyntaxKind syntaxKind,
                           std::string_view text,
                           pg_size position) noexcept
    : SyntaxNode{syntaxKind, position},
      _text{text}
{}

SyntaxTrivia::~SyntaxTrivia() noexcept
{}

} // end namespace polyglot::CodeAnalysis
