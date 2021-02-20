#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxList.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxTriviaList.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
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

ISyntaxList* SyntaxPool::createSyntaxList() noexcept
{
    _syntaxLists.push_back(std::make_unique<SyntaxList>());
    return _syntaxLists.back().get();
}

ISyntaxList* SyntaxPool::createSyntaxList(std::vector<ISyntaxNode*>&& nodes) noexcept
{
    _syntaxLists.push_back(std::make_unique<SyntaxList>(std::move(nodes)));
    return _syntaxLists.back().get();
}

ISyntaxNode* SyntaxPool::createSyntaxNode() noexcept
{
    _syntaxNodes.push_back(std::make_unique<SyntaxNode>());
    return _syntaxNodes.back().get();
}

ISyntaxToken* SyntaxPool::createSyntaxToken(SyntaxKind syntaxKind,
                                            std::string_view text,
                                            pg_size position,
                                            ISyntaxTriviaList* leadingTrivia,
                                            ISyntaxTriviaList* trailingTrivia,
                                            ISyntaxNode* parent) noexcept
{
    _syntaxTokens.push_back(std::make_unique<SyntaxToken>(syntaxKind, text, position, text.length(), leadingTrivia, trailingTrivia, parent));
    return _syntaxTokens.back().get();
}

ISyntaxTrivia* SyntaxPool::createSyntaxTrivia(SyntaxKind syntaxKind,
                                              std::string_view text,
                                              pg_size position,
                                              ISyntaxToken* token) noexcept
{
    _syntaxTrivia.push_back(std::make_unique<SyntaxTrivia>(syntaxKind, text, position, text.length(), token));
    return _syntaxTrivia.back().get();
}

ISyntaxTriviaList* SyntaxPool::createSyntaxTriviaList(ISyntaxToken* token) noexcept
{
    _syntaxTriviaLists.push_back(std::make_unique<SyntaxTriviaList>(token));
    return _syntaxTriviaLists.back().get();
}

ISyntaxTriviaList* SyntaxPool::createSyntaxTriviaList(std::vector<ISyntaxTrivia*>&& trivia,
                                                      ISyntaxToken* token) noexcept
{
    _syntaxTriviaLists.push_back(std::make_unique<SyntaxTriviaList>(std::move(trivia), token));
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

} // end namespace polyglot::CodeAnalysis
