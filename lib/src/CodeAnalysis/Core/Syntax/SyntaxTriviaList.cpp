#include "CodeAnalysis/Core/Syntax/SyntaxTriviaList.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxTrivia.hpp"
#include <cassert>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

SyntaxTriviaList::SyntaxTriviaList(LanguageSyntaxNode* underlyingNode,
                                   ISyntaxToken* token) noexcept
    : ISyntaxTriviaList{},
      _pUnderlyingNode{underlyingNode},
      _pToken{token}
{
    assert(_pUnderlyingNode != nullptr);
}

SyntaxTriviaList::~SyntaxTriviaList() noexcept
{}

ISyntaxTrivia* SyntaxTriviaList::child(pg_size index) const noexcept
{
    return SyntaxPool::createSyntaxTrivia(static_cast<LanguageSyntaxTrivia*>(_pUnderlyingNode->child(index)), _pToken);
}

TextSpan SyntaxTriviaList::span() const noexcept
{
    const pg_size pos = position();

    return TextSpan::fromBounds(pos + _pUnderlyingNode->leadingTriviaWidth(),
                                pos + _pUnderlyingNode->fullWidth() - _pUnderlyingNode->trailingTriviaWidth());
}

TextSpan SyntaxTriviaList::fullSpan() const noexcept
{
    return TextSpan{position(), _pUnderlyingNode->fullWidth()};
}

ISyntaxTrivia* SyntaxTriviaList::first() const noexcept
{
    if (_pUnderlyingNode->childCount() > 0)
        return SyntaxPool::createSyntaxTrivia(static_cast<LanguageSyntaxTrivia*>(_pUnderlyingNode->child(0)), _pToken);

    throw std::runtime_error{"invalid operation"};
}

ISyntaxTrivia* SyntaxTriviaList::last() const noexcept
{
    const pg_size count = _pUnderlyingNode->childCount();

    if (count > 0)
        return SyntaxPool::createSyntaxTrivia(static_cast<LanguageSyntaxTrivia*>(_pUnderlyingNode->child(count - 1)), _pToken);

    throw std::runtime_error{"invalid operation"};
}

} // end namespace polyglot::CodeAnalysis
