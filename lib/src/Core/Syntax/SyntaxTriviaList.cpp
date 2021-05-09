#include "SyntaxTriviaList.hpp"
#include "SyntaxTrivia.hpp"

namespace polyglot::Core::Syntax
{

SyntaxTriviaList::SyntaxTriviaList(std::vector<ISyntaxTrivia*>&& trivia,
                                   ISyntaxToken* token) noexcept
    : ISyntaxTriviaList{},
      _position{},
      _width{},
      _children{std::move(trivia)},
      _pToken{token}
{
    if (_children.size() > 0)
        _position = _children[0]->position();

    for (ISyntaxTrivia* pTrivia : _children)
        adjustWidth(pTrivia);
}

void SyntaxTriviaList::adjustWidth(ISyntaxTriva* trivia) noexcept
{
    if (trivia != nullptr)
    {
        SyntaxTrivia* pSyntaxTrivia = static_cast<SyntaxTrivia*>(trivia);
        _width += pSyntaxTrivia->_width;
    }
}

} // end namespace polyglot::Core::Syntax
