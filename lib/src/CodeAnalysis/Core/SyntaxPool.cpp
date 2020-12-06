#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

Ptr<SyntaxNode> SyntaxPool::createSyntaxNode() noexcept
{
    _syntaxNodes.push_back(std::make_unique<SyntaxNode>());
    return _syntaxNodes.back().get();
}

Ptr<SyntaxToken> SyntaxPool::createSyntaxToken() noexcept
{
    _syntaxTokens.push_back(std::make_unique<SyntaxToken>());
    return _syntaxTokens.back().get();
}

Ptr<SyntaxTrivia> SyntaxPool::createSyntaxTrivia() noexcept
{
    _syntaxTrivia.push_back(std::make_unique<SyntaxTrivia>());
    return _syntaxTrivia.back().get();
}

Ptr<SyntaxNode> SyntaxPool::add(UniquePtr<SyntaxNode> syntaxNode) noexcept
{
    assert(syntaxNode != nullptr);
    _syntaxNodes.push_back(std::move(syntaxNode));
    return _syntaxNodes.back().get();
}

Ptr<SyntaxToken> SyntaxPool::add(UniquePtr<SyntaxToken> syntaxToken) noexcept
{
    assert(syntaxToken != nullptr);
    _syntaxTokens.push_back(std::move(syntaxToken));
    return _syntaxTokens.back().get();
}

Ptr<SyntaxTrivia> SyntaxPool::add(UniquePtr<SyntaxTrivia> syntaxTrivia) noexcept
{
    assert(syntaxTrivia != nullptr);
    _syntaxTrivia.push_back(std::move(syntaxTrivia));
    return _syntaxTrivia.back().get();
}

} // end namespace polyglot::CodeAnalysis
