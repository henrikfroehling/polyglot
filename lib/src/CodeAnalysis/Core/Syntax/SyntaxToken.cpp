#include "CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

SyntaxToken::SyntaxToken(LanguageSyntaxToken* underlyingToken,
                         ISyntaxNode* parent) noexcept
    : ISyntaxToken{},
      _pUnderlyingToken{underlyingToken},
      _pParent{parent}
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

bool SyntaxToken::value() const noexcept
{
    switch (_pUnderlyingToken->syntaxKind())
    {
        case SyntaxKind::TrueKeyword: return true;
        case SyntaxKind::FalseKeyword: return false;
    }

    return false;
}

} // end namespace polyglot::CodeAnalysis
