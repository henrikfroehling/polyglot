#include "CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

SyntaxTrivia::SyntaxTrivia() noexcept
    : SyntaxNode{},
      ISyntaxTrivia{},
      _text{},
      _pToken{nullptr}
{}

SyntaxTrivia::SyntaxTrivia(SyntaxKind syntaxKind,
                           std::string_view text,
                           pg_size position,
                           pg_size fullWidth,
                           ISyntaxToken* token) noexcept
    : SyntaxNode{syntaxKind, position, fullWidth},
      ISyntaxTrivia{},
      _text{text},
      _pToken{token}
{}

SyntaxTrivia::~SyntaxTrivia() noexcept
{}

ISyntaxNode* SyntaxTrivia::child(pg_size index) const
{
    throw std::runtime_error{"invalid operation"};
}

} // end namespace polyglot::CodeAnalysis
