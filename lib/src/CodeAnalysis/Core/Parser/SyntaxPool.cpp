#include "CodeAnalysis/Core/Parser/SyntaxPool.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxList.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxTrivia.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

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

LanguageSyntaxList* SyntaxPool::createSyntaxList(std::vector<LanguageSyntaxNode*>&& nodes) noexcept
{
    _syntaxNodes.push_back(std::make_unique<LanguageSyntaxList>(std::move(nodes)));
    return static_cast<LanguageSyntaxList*>(_syntaxNodes.back().get());
}

LanguageSyntaxNode* SyntaxPool::addSyntaxNode(UniquePtr<LanguageSyntaxNode> syntaxNode) noexcept
{
    assert(syntaxNode != nullptr);
    _syntaxNodes.push_back(std::move(syntaxNode));
    return _syntaxNodes.back().get();
}

LanguageSyntaxToken* SyntaxPool::addSyntaxToken(UniquePtr<LanguageSyntaxToken> syntaxToken) noexcept
{
    assert(syntaxToken != nullptr);
    _syntaxNodes.push_back(std::move(syntaxToken));
    return static_cast<LanguageSyntaxToken*>(_syntaxNodes.back().get());
}

LanguageSyntaxTrivia* SyntaxPool::addSyntaxTrivia(UniquePtr<LanguageSyntaxTrivia> syntaxTrivia) noexcept
{
    assert(syntaxTrivia != nullptr);
    _syntaxNodes.push_back(std::move(syntaxTrivia));
    return static_cast<LanguageSyntaxTrivia*>(_syntaxNodes.back().get());
}

LanguageSyntaxList* SyntaxPool::addSyntaxList(UniquePtr<LanguageSyntaxList> syntaxList) noexcept
{
    assert(syntaxList != nullptr);
    _syntaxNodes.push_back(std::move(syntaxList));
    return static_cast<LanguageSyntaxList*>(_syntaxNodes.back().get());
}

} // end namespace polyglot::CodeAnalysis
