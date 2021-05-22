#include "Core/Syntax/SyntaxNode.hpp"
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxList.hpp"
#include "Core/Syntax/SyntaxToken.hpp"

namespace polyglot::Core::Syntax
{

SyntaxNode::SyntaxNode(SyntaxKind syntaxKind,
                       pg_size position,
                       pg_size fullWidth,
                       ISyntaxNode* parent,
                       ISyntaxTrivia* trivia) noexcept
    : ISyntaxNode{},
      _position{position},
      _fullWidth{fullWidth},
      _syntaxKind{syntaxKind},
      _flags{SyntaxFlags::None},
      _pParent{parent},
      _pTrivia{trivia},
      _pSyntaxTree{nullptr}
{}

pg_string_view SyntaxNode::text() const noexcept
{
    if (_pParent != nullptr && _pParent->syntaxTree() != nullptr)
        return _pParent->syntaxTree()->sourceText()->toString(span());

    return _pSyntaxTree != nullptr ? _pSyntaxTree->sourceText()->toString(span()) : pg_string_view{};
}

pg_string_view SyntaxNode::textIncludingTrivia() const noexcept
{
    if (_pParent != nullptr && _pParent->syntaxTree() != nullptr)
        return _pParent->syntaxTree()->sourceText()->toString(fullSpan());

    return _pSyntaxTree != nullptr ? _pSyntaxTree->sourceText()->toString(fullSpan()) : pg_string_view{};
}

pg_size SyntaxNode::leadingTriviaWidth() const noexcept
{
    SyntaxVariant firstChild = first();

    if (firstChild.isToken())
        return firstChild.token->leadingTriviaWidth();

    if (firstChild.isNode())
        return firstChild.node->leadingTriviaWidth();

    if (firstChild.isList())
        return firstChild.list->leadingTriviaWidth();

    return 0;
}

pg_size SyntaxNode::trailingTriviaWidth() const noexcept
{
    SyntaxVariant lastChild = last();

    if (lastChild.isToken())
        return lastChild.token->trailingTriviaWidth();

    if (lastChild.isNode())
        return lastChild.node->trailingTriviaWidth();

    if (lastChild.isList())
        return lastChild.list->trailingTriviaWidth();

    return 0;
}

ISyntaxTriviaList* SyntaxNode::leadingTrivia() const noexcept
{
    SyntaxVariant firstChild = first();

    if (firstChild.isToken())
        return firstChild.token->leadingTrivia();

    if (firstChild.isNode())
        return firstChild.node->leadingTrivia();

    if (firstChild.isList())
        return firstChild.list->leadingTrivia();

    return nullptr;
}

ISyntaxTriviaList* SyntaxNode::trailingTrivia() const noexcept
{
    SyntaxVariant lastChild = last();

    if (lastChild.isToken())
        return lastChild.token->trailingTrivia();

    if (lastChild.isNode())
        return lastChild.node->trailingTrivia();

    if (lastChild.isList())
        return lastChild.list->trailingTrivia();

    return nullptr;
}

bool SyntaxNode::hasMissingTokens() const noexcept
{
    ISyntaxNode* pNode = const_cast<SyntaxNode*>(this);

    for (pg_size i = 0, n = pNode->childCount(); i < n; i++)
    {
        SyntaxVariant nodeOrToken = pNode->child(i);

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

void SyntaxNode::adjustWidthAndFlags(ISyntaxList* list) noexcept
{
    if (list != nullptr)
    {
        SyntaxList* pSyntaxList = static_cast<SyntaxList*>(list);
        _fullWidth += pSyntaxList->_fullWidth;
        pSyntaxList->_pParent = this;
    }
}

void SyntaxNode::setTriviaParent(ISyntaxTrivia* trivia) noexcept
{
    _pParent = nullptr;
    _pTrivia = trivia;
}

void SyntaxNode::setSyntaxTree(ISyntaxTree* syntaxTree) noexcept
{
    _pSyntaxTree = syntaxTree;
}

pg_string SyntaxNode::toString() const noexcept
{
    pg_stringstream str;
    str << L"Node(Position: " << _position << L", Kind: " << syntaxKindName(_syntaxKind) << L", Value: \"" << text() << L"\", Width: " << width() << L")";
    return str.str();
}

pg_string SyntaxNode::toShortString() const noexcept
{
    pg_stringstream str;
    str << L"Node: " << syntaxKindName(_syntaxKind) << L" " << fullSpan();
    return str.str();
}

} // end namespace polyglot::Core::Syntax
