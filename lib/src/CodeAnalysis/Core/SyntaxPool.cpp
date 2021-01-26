#include "CodeAnalysis/Core/SyntaxPool.hpp"
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
                                                   pg_size position) noexcept
{
    _syntaxTokens.push_back(std::make_unique<LanguageSyntaxToken>(syntaxKind, text, position));
    return _syntaxTokens.back().get();
}

LanguageSyntaxTrivia* SyntaxPool::createSyntaxTrivia(SyntaxKind syntaxKind,
                                                     std::string_view text,
                                                     pg_size position) noexcept
{
    _syntaxTrivia.push_back(std::make_unique<LanguageSyntaxTrivia>(syntaxKind, text, position));
    return _syntaxTrivia.back().get();
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
    _syntaxTokens.push_back(std::move(syntaxToken));
    return _syntaxTokens.back().get();
}

LanguageSyntaxTrivia* SyntaxPool::addSyntaxTrivia(UniquePtr<LanguageSyntaxTrivia> syntaxTrivia) noexcept
{
    assert(syntaxTrivia != nullptr);
    _syntaxTrivia.push_back(std::move(syntaxTrivia));
    return _syntaxTrivia.back().get();
}

} // end namespace polyglot::CodeAnalysis
