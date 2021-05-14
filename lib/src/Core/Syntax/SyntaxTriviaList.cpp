#include "Core/Syntax/SyntaxTriviaList.hpp"
#include <sstream>
#include "Core/Syntax/SyntaxTrivia.hpp"

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

void SyntaxTriviaList::adjustWidth(ISyntaxTrivia* trivia) noexcept
{
    if (trivia != nullptr)
    {
        SyntaxTrivia* pSyntaxTrivia = static_cast<SyntaxTrivia*>(trivia);
        _width += pSyntaxTrivia->_width;
    }
}

std::string SyntaxTriviaList::toString() const noexcept
{
    std::stringstream str;
    str << "TriviaList(" << _position << ", \"" << text() << "\"" << "," << width() << ")";
    return str.str();
}

} // end namespace polyglot::Core::Syntax
