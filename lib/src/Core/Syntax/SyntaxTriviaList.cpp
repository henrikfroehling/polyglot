#include "Core/Syntax/SyntaxTriviaList.hpp"
#include <sstream>
#include "polyglot/Core/Syntax/ISyntaxNode.hpp"
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/ISyntaxTree.hpp"
#include "polyglot/Core/Text/SourceText.hpp"
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

std::string_view SyntaxTriviaList::text() const noexcept
{
    if (_pToken != nullptr && _pToken->parent() != nullptr && _pToken->parent()->syntaxTree() != nullptr)
    {
        ISyntaxTrivia* pFirstTrivia = first();

        if (pFirstTrivia != nullptr)
        {
            ISyntaxTrivia* pLastTrivia = last();
            const pg_size position = pFirstTrivia->position();
            pg_size endPosition = pFirstTrivia->endPosition();

            if (pLastTrivia != nullptr)
                endPosition = pLastTrivia->endPosition();

            const Text::TextSpan triviaSpan = Text::TextSpan::fromBounds(position, endPosition);
            return _pToken->parent()->syntaxTree()->sourceText()->toString(triviaSpan);
        }
    }

    return std::string_view{};
}

void SyntaxTriviaList::adjustWidth(ISyntaxTrivia* trivia) noexcept
{
    if (trivia != nullptr)
    {
        SyntaxTrivia* pSyntaxTrivia = static_cast<SyntaxTrivia*>(trivia);
        _width += pSyntaxTrivia->_width;
        pSyntaxTrivia->_pToken = _pToken;
    }
}

void SyntaxTriviaList::setToken(ISyntaxToken* token) noexcept
{
    _pToken = token;

    for (ISyntaxTrivia* trivia : _children)
    {
        SyntaxTrivia* pSyntaxTrivia = static_cast<SyntaxTrivia*>(trivia);
        pSyntaxTrivia->_pToken = token;
    }
}

std::string SyntaxTriviaList::toString() const noexcept
{
    std::stringstream str;
    str << "TriviaList(Position: " << _position << ", Width: " << width() << ")";
    return str.str();
}

std::string SyntaxTriviaList::toShortString() const noexcept
{
    std::stringstream str;
    str << "TriviaList: " << span();
    return str.str();
}

} // end namespace polyglot::Core::Syntax
