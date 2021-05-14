#include "Core/Syntax/SyntaxList.hpp"
#include <sstream>
#include "polyglot/Core/Syntax/ISyntaxNode.hpp"
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxNode.hpp"
#include "Core/Syntax/SyntaxToken.hpp"

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
    {
        SyntaxVariant child = _children[0];

        if (child.isNode())
            _position = child.node->position();
        else if (child.isToken())
            _position = child.token->position();
        else if (child.isList())
            _position = child.list->position();
    }

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
    for (const SyntaxVariant& nodeOrToken : _children)
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

std::string SyntaxList::toString() const noexcept
{
    std::stringstream str;
    str << "SyntaxList(" << _position << ", " << syntaxKindName(_syntaxKind) << ", \"" << text() << "\"" << "," << width() << ")";
    return str.str();
}

} // end namespace polyglot::Core::Syntax
