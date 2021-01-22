#include "CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ISyntaxTriviaList.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

SyntaxToken::SyntaxToken(LanguageSyntaxNode* underlyingNode,
                         ISyntaxNode* parent) noexcept
    : ISyntaxToken{},
      _pUnderlyingNode{underlyingNode},
      _pParent{parent},
      _pLeadingTrivia{nullptr},
      _pTrailingTrivia{nullptr}
{
    assert(underlyingNode != nullptr);
}

SyntaxToken::~SyntaxToken() noexcept
{}

TextSpan SyntaxToken::span() const noexcept
{
    return TextSpan{_pUnderlyingNode->position() + _pUnderlyingNode->leadingTriviaWidth(),
                    _pUnderlyingNode->width()};
}

bool SyntaxToken::value() const noexcept
{
    switch (_pUnderlyingNode->syntaxKind())
    {
        case SyntaxKind::TrueKeyword: return true;
        case SyntaxKind::FalseKeyword: return false;
    }

    return false;
}

bool SyntaxToken::hasLeadingTrivia() const noexcept
{
    return _pLeadingTrivia != nullptr && _pLeadingTrivia->count() != 0;
}

bool SyntaxToken::hasTrailingTrivia() const noexcept
{
    return _pTrailingTrivia != nullptr && _pTrailingTrivia->count() != 0;
}

} // end namespace polyglot::CodeAnalysis
