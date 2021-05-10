#include "Core/Syntax/SyntaxNode.hpp"
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxToken.hpp"

namespace polyglot::Core::Syntax
{

SyntaxNode::SyntaxNode() noexcept
    : ISyntaxNode{},
      _position{},
      _fullWidth{},
      _syntaxKind{SyntaxKind::None},
      _flags{SyntaxFlags::None},
      _pParent{nullptr}
{}

SyntaxNode::SyntaxNode(SyntaxKind syntaxKind,
                       pg_size position,
                       pg_size fullWidth,
                       ISyntaxNode* parent) noexcept
    : ISyntaxNode{},
      _position{position},
      _fullWidth{fullWidth},
      _syntaxKind{syntaxKind},
      _flags{SyntaxFlags::None},
      _pParent{parent}
{}

pg_size SyntaxNode::leadingTriviaWidth() const noexcept
{
    ISyntaxToken* pFirstToken = firstToken();

    if (pFirstToken != nullptr)
        return pFirstToken->leadingTriviaWidth();

    return 0;
}

pg_size SyntaxNode::trailingTriviaWidth() const noexcept
{
    ISyntaxToken* pLastToken = lastToken();

    if (pLastToken != nullptr)
        return pLastToken->trailingTriviaWidth();

    return 0;
}

ISyntaxTriviaList* SyntaxNode::leadingTrivia() const noexcept
{
    ISyntaxToken* pFirstToken = firstToken();

    if (pFirstToken != nullptr)
        return pFirstToken->leadingTrivia();

    return nullptr;
}

ISyntaxTriviaList* SyntaxNode::trailingTrivia() const noexcept
{
    ISyntaxToken* pLastToken = lastToken();

    if (pLastToken != nullptr)
        return pLastToken->trailingTrivia();

    return nullptr;
}

bool SyntaxNode::hasMissingTokens() const noexcept
{
    for (pg_size i = 0, n = pNode->childCount(); i < n; i++)
    {
        SyntaxNodeOrToken nodeOrToken = pNode->child(i);

        if (nodeOrToken->isToken())
        {
            if (nodeOrToken->token->isMissing())
                return true;
        }
        else if (nodeOrToken->isNode())
        {
            if (nodeOrToken->node->hasMissingTokens())
                return true;
        }
    }

    return false;
}

ISyntaxToken* SyntaxNode::firstToken() const noexcept
{
    ISyntaxNode* pNode = const_cast<SyntaxNode*>(this);

    do
    {
        for (pg_size i = 0, n = pNode->childCount(); i < n; i++)
        {
            SyntaxNodeOrToken nodeOrToken = pNode->child(i);

            if (nodeOrToken->isToken())
                return nodeOrToken->token;

            pNode = nodeOrToken->node;
            break;
        }
    }
    while (pNode != nullptr && pNode->childCount() > 0);

    return nullptr;
}

ISyntaxToken* SyntaxNode::lastToken() const noexcept
{
    ISyntaxNode* pNode = const_cast<SyntaxNode*>(this);

    do
    {
        for (pg_size i = pNode->childCount() - 1; i > -1; i--)
        {
            SyntaxNodeOrToken nodeOrToken = pNode->child(i);

            if (nodeOrToken->isToken())
                return nodeOrToken->token;

            pNode = nodeOrToken->node;
            break;
        }
    }
    while (pNode != nullptr && pNode->childCount() > 0);

    return nullptr;
}

void SyntaxNode::adjustWidthAndFlags(ISyntaxNode* node) noexcept
{
    if (node != nullptr)
    {
        SyntaxNode* pSyntaxNode = static_cast<SyntaxNode*>(node);
        _fullWidth += pSyntaxNode->_fullWidth;
        _flags |= pSyntaxNode->_flags;
        pSyntaxNode->_pParent = this;
    }
}

void SyntaxNode::adjustWidthAndFlags(ISyntaxToken* token) noexcept
{
    if (token != nullptr)
    {
        SyntaxToken* pSyntaxToken = static_cast<SyntaxToken*>(token);
        _fullWidth += pSyntaxToken->_fullWidth;
        pSyntaxToken->_pParent = this;
    }
}

} // end namespace polyglot::Core::Syntax
