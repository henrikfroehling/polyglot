#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxList.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

SyntaxPool::SyntaxPool() noexcept
    : _syntaxNodes{},
      _syntaxTrivia{}
{}

SyntaxPool::SyntaxPool(SyntaxPool&& other) noexcept
    : _syntaxNodes{std::move(other._syntaxNodes)},
      _syntaxTrivia{std::move(other._syntaxTrivia)}
{}

SyntaxPool& SyntaxPool::operator=(SyntaxPool&& other) noexcept
{
    if (this != &other)
    {
        _syntaxNodes = std::move(other._syntaxNodes);
        _syntaxTrivia = std::move(other._syntaxTrivia);
    }

    return *this;
}

LanguageSyntaxNode* SyntaxPool::createSyntaxNode() noexcept
{
    _syntaxNodes.push_back(std::make_unique<LanguageSyntaxNode>());
    return _syntaxNodes.back().get();
}

LanguageSyntaxToken* SyntaxPool::createSyntaxToken(SyntaxKind syntaxKind,
                                                   std::string_view text,
                                                   pg_size position,
                                                   LanguageSyntaxList* leadingTrivia,
                                                   LanguageSyntaxList* trailingTrivia) noexcept
{
    _syntaxNodes.push_back(std::make_unique<LanguageSyntaxToken>(syntaxKind, text, position, text.length(), leadingTrivia, trailingTrivia));
    return static_cast<LanguageSyntaxToken*>(_syntaxNodes.back().get());
}

LanguageSyntaxTrivia* SyntaxPool::createSyntaxTrivia(SyntaxKind syntaxKind,
                                                     std::string_view text,
                                                     pg_size position) noexcept
{
    _syntaxNodes.push_back(std::make_unique<LanguageSyntaxTrivia>(syntaxKind, text, position));
    return static_cast<LanguageSyntaxTrivia*>(_syntaxNodes.back().get());
}

ISyntaxTrivia* SyntaxPool::createSyntaxTrivia(LanguageSyntaxTrivia* trivia,
                                              ISyntaxToken* token) noexcept
{
    _syntaxTrivia.push_back(std::make_unique<SyntaxTrivia>(trivia, token));
    return _syntaxTrivia.back().get();
}

LanguageSyntaxList* SyntaxPool::createSyntaxList(std::vector<LanguageSyntaxNode*>&& nodes) noexcept
{
    _syntaxNodes.push_back(std::make_unique<LanguageSyntaxList>(std::move(nodes)));
    return static_cast<LanguageSyntaxList*>(_syntaxNodes.back().get());
}

LanguageSyntaxNode* SyntaxPool::addSyntaxNode(UniquePtr<LanguageSyntaxNode>&& syntaxNode) noexcept
{
    assert(syntaxNode != nullptr);
    _syntaxNodes.push_back(std::move(syntaxNode));
    return _syntaxNodes.back().get();
}

LanguageSyntaxToken* SyntaxPool::addSyntaxToken(UniquePtr<LanguageSyntaxToken>&& syntaxToken) noexcept
{
    assert(syntaxToken != nullptr);
    _syntaxNodes.push_back(std::move(syntaxToken));
    return static_cast<LanguageSyntaxToken*>(_syntaxNodes.back().get());
}

LanguageSyntaxTrivia* SyntaxPool::addSyntaxTrivia(UniquePtr<LanguageSyntaxTrivia>&& syntaxTrivia) noexcept
{
    assert(syntaxTrivia != nullptr);
    _syntaxNodes.push_back(std::move(syntaxTrivia));
    return static_cast<LanguageSyntaxTrivia*>(_syntaxNodes.back().get());
}

LanguageSyntaxList* SyntaxPool::addSyntaxList(UniquePtr<LanguageSyntaxList>&& syntaxList) noexcept
{
    assert(syntaxList != nullptr);
    _syntaxNodes.push_back(std::move(syntaxList));
    return static_cast<LanguageSyntaxList*>(_syntaxNodes.back().get());
}

void SyntaxPool::reserve(pg_size count) noexcept
{
    _syntaxNodes.reserve(count);
    _syntaxTrivia.reserve(count);
}

} // end namespace polyglot::CodeAnalysis
