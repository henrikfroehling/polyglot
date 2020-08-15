#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxToken::SyntaxToken() noexcept
    : SyntaxNode{SyntaxKind::None},
      _text{},
      _leadingTrivia{},
      _trailingTrivia{},
      _contextualKind{SyntaxKind::None}
{}

SyntaxToken::SyntaxToken(SyntaxKind syntaxKind) noexcept
    : SyntaxNode{syntaxKind},
      _text{},
      _leadingTrivia{},
      _trailingTrivia{},
      _contextualKind{SyntaxKind::None}
{}

SyntaxToken::SyntaxToken(SyntaxKind syntaxKind,
                         std::string_view text) noexcept
    : SyntaxNode{syntaxKind},
      _text{text},
      _leadingTrivia{},
      _trailingTrivia{},
      _contextualKind{SyntaxKind::None}
{}

void SyntaxToken::setLeadingTrivia(std::vector<SyntaxTriviaPtr>&& leadingTrivia) noexcept
{
    _leadingTrivia = std::move(leadingTrivia);
}

void SyntaxToken::setTrailingTrivia(std::vector<SyntaxTriviaPtr>&& trailingTrivia) noexcept
{
    _trailingTrivia = std::move(trailingTrivia);
}

} // end namespace polyglot::CodeAnalysis
