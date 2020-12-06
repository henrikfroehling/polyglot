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

SyntaxToken::SyntaxToken(SyntaxKind syntaxKind,
                         std::string_view text) noexcept
    : SyntaxNode{syntaxKind},
      _text{text},
      _leadingTrivia{},
      _trailingTrivia{},
      _contextualKind{SyntaxKind::None}
{}

void SyntaxToken::setLeadingTrivia(std::vector<Ptr<SyntaxNode>>&& leadingTrivia) noexcept
{
    _leadingTrivia = std::move(leadingTrivia);
}

void SyntaxToken::setTrailingTrivia(std::vector<Ptr<SyntaxNode>>&& trailingTrivia) noexcept
{
    _trailingTrivia = std::move(trailingTrivia);
}

bool SyntaxToken::value() const noexcept
{
    switch (_syntaxKind)
    {
        case SyntaxKind::TrueKeyword: return true;
        case SyntaxKind::FalseKeyword: return false;
    }

    return false;
}

} // end namespace polyglot::CodeAnalysis
