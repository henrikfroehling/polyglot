#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

SyntaxToken::SyntaxToken() noexcept
    : SyntaxNode{SyntaxKind::None},
      _text{},
      _leadingTrivia{},
      _trailingTrivia{}
{}

SyntaxToken::SyntaxToken(SyntaxKind syntaxKind,
                         std::string_view text) noexcept
    : SyntaxNode{syntaxKind},
      _text{text},
      _leadingTrivia{},
      _trailingTrivia{}
{}

void SyntaxToken::setLeadingTrivia(std::vector<SyntaxNode*>&& leadingTrivia) noexcept
{
    _leadingTrivia = std::move(leadingTrivia);
}

void SyntaxToken::setTrailingTrivia(std::vector<SyntaxNode*>&& trailingTrivia) noexcept
{
    _trailingTrivia = std::move(trailingTrivia);
}

void SyntaxToken::addLeadingTrivia(SyntaxNode* leadingTrivia) noexcept
{
    assert(leadingTrivia != nullptr);
    _leadingTrivia.push_back(leadingTrivia);
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
