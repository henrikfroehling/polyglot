#include "CodeAnalysis/Core/Syntax/SyntaxTriviaList.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

SyntaxTriviaList::SyntaxTriviaList(ISyntaxToken* token) noexcept
    : ISyntaxTriviaList{},
      SyntaxNode{},
      _children{},
      _pToken{token}
{}

SyntaxTriviaList::SyntaxTriviaList(std::vector<ISyntaxTrivia*>&& trivia,
                                   ISyntaxToken* token) noexcept
    : ISyntaxTriviaList{},
      SyntaxNode{},
      _children{std::move(trivia)},
      _pToken{token}
{
    if (_children.size() > 0)
        _position = _children[0]->position();

    for (ISyntaxTrivia* pChild : _children)
        adjustWidthAndFlags(pChild);
}

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
