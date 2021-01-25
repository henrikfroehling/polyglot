#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxNode.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxTrivia.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

SyntaxPool::SyntaxPool() noexcept
    : _syntaxNodes{}
{}

LanguageSyntaxNode* SyntaxPool::createSyntaxNode() noexcept
{
    _syntaxNodes.push_back(std::make_unique<LanguageSyntaxNode>());
    return _syntaxNodes.back().get();
}

LanguageSyntaxToken* SyntaxPool::createSyntaxToken(SyntaxKind syntaxKind,
                                                   std::string_view text,
                                                   pg_size position) noexcept
{
    _syntaxNodes.push_back(std::make_unique<LanguageSyntaxToken>(syntaxKind, text, position));
    return static_cast<LanguageSyntaxToken*>(_syntaxNodes.back().get());
}

LanguageSyntaxTrivia* SyntaxPool::createSyntaxTrivia(SyntaxKind syntaxKind,
                                                     std::string_view text,
                                                     pg_size position) noexcept
{
    _syntaxNodes.push_back(std::make_unique<LanguageSyntaxTrivia>(syntaxKind, text, position));
    return static_cast<LanguageSyntaxTrivia*>(_syntaxNodes.back().get());
}

} // end namespace polyglot::CodeAnalysis
