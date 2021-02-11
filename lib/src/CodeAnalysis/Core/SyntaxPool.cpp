#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

SyntaxPool::SyntaxPool() noexcept
    : _languageSyntaxNodes{},
      _languageSyntaxTokens{},
      _languageSyntaxTrivia{},
      _languageSyntaxLists{},
      _syntaxTrivia{}
{}

SyntaxPool::SyntaxPool(SyntaxPool&& other) noexcept
    : _languageSyntaxNodes{std::move(other._languageSyntaxNodes)},
      _languageSyntaxTokens{std::move(other._languageSyntaxTokens)},
      _languageSyntaxTrivia{std::move(other._languageSyntaxTrivia)},
      _languageSyntaxLists{std::move(other._languageSyntaxLists)},
      _syntaxTrivia{std::move(other._syntaxTrivia)}
{}

SyntaxPool& SyntaxPool::operator=(SyntaxPool&& other) noexcept
{
    if (this != &other)
    {
        _languageSyntaxNodes = std::move(other._languageSyntaxNodes);
        _languageSyntaxTokens = std::move(other._languageSyntaxTokens);
        _languageSyntaxTrivia = std::move(other._languageSyntaxTrivia);
        _languageSyntaxLists = std::move(other._languageSyntaxLists);
        _syntaxTrivia = std::move(other._syntaxTrivia);
    }

    return *this;
}

LanguageSyntaxNode* SyntaxPool::createSyntaxNode() noexcept
{
    _languageSyntaxNodes.push_back(std::make_unique<LanguageSyntaxNode>());
    return _languageSyntaxNodes.back().get();
}

LanguageSyntaxToken* SyntaxPool::createSyntaxToken(SyntaxKind syntaxKind,
                                                   std::string_view text,
                                                   pg_size position,
                                                   LanguageSyntaxList* leadingTrivia,
                                                   LanguageSyntaxList* trailingTrivia) noexcept
{
    _languageSyntaxTokens.push_back(std::make_unique<LanguageSyntaxToken>(syntaxKind, text, position, text.length(), leadingTrivia, trailingTrivia));
    return _languageSyntaxTokens.back().get();
}

LanguageSyntaxTrivia* SyntaxPool::createSyntaxTrivia(SyntaxKind syntaxKind,
                                                     std::string_view text,
                                                     pg_size position) noexcept
{
    _languageSyntaxTrivia.push_back(std::make_unique<LanguageSyntaxTrivia>(syntaxKind, text, position));
    return _languageSyntaxTrivia.back().get();
}

ISyntaxTrivia* SyntaxPool::createSyntaxTrivia(LanguageSyntaxTrivia* trivia,
                                              ISyntaxToken* token) noexcept
{
    _syntaxTrivia.push_back(std::make_unique<SyntaxTrivia>(trivia, token));
    return _syntaxTrivia.back().get();
}

LanguageSyntaxList* SyntaxPool::createSyntaxList() noexcept
{
    _languageSyntaxLists.push_back(std::make_unique<LanguageSyntaxList>());
    return _languageSyntaxLists.back().get();
}

LanguageSyntaxList* SyntaxPool::createSyntaxList(std::vector<LanguageSyntaxNode*>&& nodes) noexcept
{
    _languageSyntaxLists.push_back(std::make_unique<LanguageSyntaxList>(std::move(nodes)));
    return _languageSyntaxLists.back().get();
}

LanguageSyntaxNode* SyntaxPool::addSyntaxNode(UniquePtr<LanguageSyntaxNode>&& syntaxNode) noexcept
{
    assert(syntaxNode != nullptr);
    _languageSyntaxNodes.push_back(std::move(syntaxNode));
    return _languageSyntaxNodes.back().get();
}

LanguageSyntaxToken* SyntaxPool::addSyntaxToken(UniquePtr<LanguageSyntaxToken>&& syntaxToken) noexcept
{
    assert(syntaxToken != nullptr);
    _languageSyntaxTokens.push_back(std::move(syntaxToken));
    return _languageSyntaxTokens.back().get();
}

LanguageSyntaxTrivia* SyntaxPool::addSyntaxTrivia(UniquePtr<LanguageSyntaxTrivia>&& syntaxTrivia) noexcept
{
    assert(syntaxTrivia != nullptr);
    _languageSyntaxTrivia.push_back(std::move(syntaxTrivia));
    return _languageSyntaxTrivia.back().get();
}

LanguageSyntaxList* SyntaxPool::addSyntaxList(UniquePtr<LanguageSyntaxList>&& syntaxList) noexcept
{
    assert(syntaxList != nullptr);
    _languageSyntaxLists.push_back(std::move(syntaxList));
    return _languageSyntaxLists.back().get();
}

} // end namespace polyglot::CodeAnalysis
