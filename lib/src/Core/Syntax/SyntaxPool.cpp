#include "Core/Syntax/SyntaxPool.hpp"
#include <cassert>
#include "Core/Syntax/SyntaxList.hpp"
#include "Core/Syntax/SyntaxNode.hpp"
#include "Core/Syntax/SyntaxToken.hpp"
#include "Core/Syntax/SyntaxTrivia.hpp"
#include "Core/Syntax/SyntaxTriviaList.hpp"

namespace polyglot::Core::Syntax
{

SyntaxPool::SyntaxPool() noexcept
    : _syntaxLists{},
      _syntaxNodes{},
      _syntaxTokens{},
      _syntaxTrivia{},
      _syntaxTriviaLists{}
{}

SyntaxPool::SyntaxPool(SyntaxPool&& other) noexcept
    : _syntaxLists{ std::move(other._syntaxLists) },
      _syntaxNodes{std::move(other._syntaxNodes)},
      _syntaxTokens{std::move(other._syntaxTokens)},
      _syntaxTrivia{std::move(other._syntaxTrivia)},
      _syntaxTriviaLists{std::move(other._syntaxTriviaLists)}
{}

SyntaxPool& SyntaxPool::operator=(SyntaxPool&& other) noexcept
{
    if (this != &other)
    {
        _syntaxLists = std::move(other._syntaxLists);
        _syntaxNodes = std::move(other._syntaxNodes);
        _syntaxTokens = std::move(other._syntaxTokens);
        _syntaxTrivia = std::move(other._syntaxTrivia);
        _syntaxTriviaLists = std::move(other._syntaxTriviaLists);
    }

    return *this;
}

ISyntaxList* SyntaxPool::createSyntaxList(SyntaxKind syntaxKind,
                                          std::vector<SyntaxVariant>&& nodes) noexcept
{
    _syntaxLists.emplace_back(new SyntaxList{syntaxKind, std::move(nodes)});
    return _syntaxLists.back().get();
}

ISyntaxToken* SyntaxPool::createSyntaxToken(SyntaxKind syntaxKind,
                                            std::string_view text,
                                            pg_size position,
                                            ISyntaxTriviaList* leadingTrivia,
                                            ISyntaxTriviaList* trailingTrivia,
                                            ISyntaxNode* parent) noexcept
{
    _syntaxTokens.emplace_back(new SyntaxToken{syntaxKind, text, position, text.length(), leadingTrivia, trailingTrivia, parent});
    return _syntaxTokens.back().get();
}

ISyntaxTrivia* SyntaxPool::createSyntaxTrivia(SyntaxKind syntaxKind,
                                              std::string_view text,
                                              pg_size position,
                                              ISyntaxToken* token) noexcept
{
    _syntaxTrivia.emplace_back(new SyntaxTrivia{syntaxKind, text, position, text.length(), token});
    return _syntaxTrivia.back().get();
}

ISyntaxTriviaList* SyntaxPool::createSyntaxTriviaList(std::vector<ISyntaxTrivia*>&& trivia,
                                                      ISyntaxToken* token) noexcept
{
    _syntaxTriviaLists.emplace_back(new SyntaxTriviaList{std::move(trivia), token});
    return _syntaxTriviaLists.back().get();
}

ISyntaxList* SyntaxPool::addSyntaxList(UniquePtr<ISyntaxList>&& syntaxList) noexcept
{
    assert(syntaxList != nullptr);
    _syntaxLists.push_back(std::move(syntaxList));
    return _syntaxLists.back().get();
}

ISyntaxNode* SyntaxPool::addSyntaxNode(UniquePtr<ISyntaxNode>&& syntaxNode) noexcept
{
    assert(syntaxNode != nullptr);
    _syntaxNodes.push_back(std::move(syntaxNode));
    return _syntaxNodes.back().get();
}

ISyntaxToken* SyntaxPool::addSyntaxToken(UniquePtr<ISyntaxToken>&& syntaxToken) noexcept
{
    assert(syntaxToken != nullptr);
    _syntaxTokens.push_back(std::move(syntaxToken));
    return _syntaxTokens.back().get();
}

ISyntaxTrivia* SyntaxPool::addSyntaxTrivia(UniquePtr<ISyntaxTrivia>&& syntaxTrivia) noexcept
{
    assert(syntaxTrivia != nullptr);
    _syntaxTrivia.push_back(std::move(syntaxTrivia));
    return _syntaxTrivia.back().get();
}

ISyntaxTriviaList* SyntaxPool::addSyntaxTriviaList(UniquePtr<ISyntaxTriviaList>&& syntaxTriviaList) noexcept
{
    assert(syntaxTriviaList != nullptr);
    _syntaxTriviaLists.push_back(std::move(syntaxTriviaList));
    return _syntaxTriviaLists.back().get();
}

} // end namespace polyglot::Core::Syntax
