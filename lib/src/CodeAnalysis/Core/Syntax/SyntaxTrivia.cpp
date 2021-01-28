#include "CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

SyntaxTrivia::SyntaxTrivia(LanguageSyntaxTrivia* underlyingTrivia,
                           ISyntaxToken* token) noexcept
    : ISyntaxTrivia{},
      _pUnderlyingTrivia{underlyingTrivia},
      _pToken{token}
{
    assert(_pUnderlyingTrivia != nullptr);
}

SyntaxTrivia::~SyntaxTrivia() noexcept
{}

TextSpan SyntaxTrivia::span() const noexcept
{
    return TextSpan{_pUnderlyingTrivia->position() + _pUnderlyingTrivia->leadingTriviaWidth(),
                    _pUnderlyingTrivia->width()};
}

} // end namespace polyglot::CodeAnalysis
