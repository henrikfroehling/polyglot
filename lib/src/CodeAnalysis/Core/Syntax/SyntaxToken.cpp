#include "CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ISyntaxTriviaList.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

SyntaxToken::SyntaxToken(LanguageSyntaxToken* underlyingToken,
                         ISyntaxNode* parent) noexcept
    : ISyntaxToken{},
      _pUnderlyingToken{underlyingToken},
      _pParent{parent},
      _pLeadingTrivia{nullptr},
      _pTrailingTrivia{nullptr}
{
    assert(_pUnderlyingToken != nullptr);
}

SyntaxToken::~SyntaxToken() noexcept
{}

TextSpan SyntaxToken::span() const noexcept
{
    return TextSpan{_pUnderlyingToken->position() + _pUnderlyingToken->leadingTriviaWidth(),
                    _pUnderlyingToken->width()};
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
