#include "SyntaxList.hpp"
#include "polyglot/Core/Syntax/ISyntaxNode.hpp"
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "SyntaxNode.hpp"
#include "SyntaxToken.hpp"

namespace polyglot::Core::Syntax
{

SyntaxList::SyntaxList(SyntaxKind syntaxKind,
                       std::vector<SyntaxVariant>&& children,
                       pg_size position,
                       pg_size fullWidth,
                       ISyntaxNode* parent) noexcept
    : ISyntaxList{},
      _position{position},
      _fullWidth{fullWidth},
      _syntaxKind{syntaxKind},
      _pParent{parent},
      _children{std::move(children)}
{
    if (_children.size() > 0)
        _position = _children[0]->position();

    for (SyntaxVariant& child : _children)
    {
        if (child.isNode())
            adjustWidthAndFlags(child.node);
        else if (child.isToken())
            adjustWidthAndFlags(child.token);
    }
}

pg_size SyntaxList::leadingTriviaWidth() const noexcept
{
    SyntaxVariant nodeOrToken = first();

    if (nodeOrToken.isToken())
        return nodeOrToken.token->leadingTriviaWidth();
    else if (nodeOrToken.isNode())
        return nodeOrToken.node->leadingTriviaWidth();

    return 0;
}

pg_size SyntaxList::trailingTriviaWidth() const noexcept
{
    SyntaxVariant nodeOrToken = last();

    if (nodeOrToken.isToken())
        return nodeOrToken.token->trailingTriviaWidth();
    else if (nodeOrToken.isNode())
        return nodeOrToken.node->trailingTriviaWidth();

    return 0;
}

ISyntaxTriviaList* SyntaxList::leadingTrivia() const noexcept
{
    SyntaxVariant nodeOrToken = first();

    if (nodeOrToken.isToken())
        return nodeOrToken.token->leadingTrivia();
    else if (nodeOrToken.isNode())
        return nodeOrToken.node->leadingTrivia();

    return nullptr;
}

ISyntaxTriviaList* SyntaxList::trailingTrivia() const noexcept
{
    SyntaxVariant nodeOrToken = last();

    if (nodeOrToken.isToken())
        return nodeOrToken.token->trailingTrivia();
    else if (nodeOrToken.isNode())
        return nodeOrToken.node->trailingTrivia();

    return nullptr;
}

bool SyntaxList::hasMissingTokens() const noexcept
{
    for (SyntaxVariant& nodeOrToken : _children)
    {
        if (nodeOrToken.isToken())
        {
            if (nodeOrToken.token->isMissing())
                return true;
        }
        else if (nodeOrToken.isNode())
        {
            if (nodeOrToken.node->hasMissingTokens())
                return true;
        }
    }

    return false;
}

void SyntaxList::adjustWidthAndFlags(ISyntaxList* list) noexcept
{
    if (list != nullptr)
    {
        SyntaxList* pSyntaxList = static_cast<SyntaxList*>(list);
        _fullWidth += pSyntaxList->_fullWidth;
    }
}

void SyntaxList::adjustWidthAndFlags(ISyntaxNode* node) noexcept
{
    if (node != nullptr)
    {
        SyntaxNode* pSyntaxNode = static_cast<SyntaxNode*>(node);
        _fullWidth += pSyntaxNode->_fullWidth;
    }
}

void SyntaxList::adjustWidthAndFlags(ISyntaxToken* token) noexcept
{
    if (token != nullptr)
    {
        SyntaxToken* pSyntaxToken = static_cast<SyntaxToken*>(token);
        _fullWidth += pSyntaxToken->_fullWidth;
    }
}

} // end namespace polyglot::Core::Syntax
