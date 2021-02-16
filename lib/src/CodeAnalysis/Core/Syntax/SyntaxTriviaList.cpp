#include "CodeAnalysis/Core/Syntax/SyntaxTriviaList.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxTrivia.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

SyntaxTriviaList::SyntaxTriviaList(ISyntaxToken* token) noexcept
    : SyntaxNode{},
      ISyntaxTriviaList{},
      _children{},
      _pToken{token}
{}

SyntaxTriviaList::~SyntaxTriviaList() noexcept
{}

ISyntaxToken* SyntaxTriviaList::token() const noexcept
{
    return _pToken;
}

void SyntaxTriviaList::add(ISyntaxTrivia* trivia) noexcept
{
    assert(trivia != nullptr);

    if (_children.empty())
        _position = trivia->position();

    _children.push_back(trivia);
    adjustWidthAndFlags(trivia);
}

} // end namespace polyglot::CodeAnalysis
