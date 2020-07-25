#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxToken::SyntaxToken() noexcept
    : SyntaxNode{SyntaxKind::None},
    _text{},
    _leadingTrivia{},
    _trailingTrivia{}
{}

SyntaxToken::SyntaxToken(SyntaxKind syntaxKind) noexcept
    : SyntaxNode{syntaxKind},
      _text{},
      _leadingTrivia{},
      _trailingTrivia{}
{}

SyntaxToken::SyntaxToken(SyntaxKind syntaxKind,
                         pg_size position,
                         std::string_view text) noexcept
    : SyntaxNode{syntaxKind, position},
      _text{text},
      _leadingTrivia{},
      _trailingTrivia{}
{}

void SyntaxToken::addLeadingTrivia(std::shared_ptr<SyntaxTrivia> leadingTrivia) noexcept
{
    _leadingTrivia.push_back(std::move(leadingTrivia));
}

void SyntaxToken::addTrailingTrivia(std::shared_ptr<SyntaxTrivia> trailingTrivia) noexcept
{
    _trailingTrivia.push_back(std::move(trailingTrivia));
}

} // end namespace polyglot::CodeAnalysis
