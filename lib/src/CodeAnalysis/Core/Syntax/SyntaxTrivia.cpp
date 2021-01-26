#include "CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

SyntaxTrivia::SyntaxTrivia(LanguageSyntaxNode* underlyingNode,
                           ISyntaxToken* token) noexcept
    : ISyntaxTrivia{},
      _pUnderlyingNode{underlyingNode},
      _pToken{token}
{
    assert(_pUnderlyingNode != nullptr);
}

SyntaxTrivia::~SyntaxTrivia() noexcept
{}

TextSpan SyntaxTrivia::span() const noexcept
{
    return TextSpan{_pUnderlyingNode->position() + _pUnderlyingNode->leadingTriviaWidth(),
                    _pUnderlyingNode->width()};
}

} // end namespace polyglot::CodeAnalysis
