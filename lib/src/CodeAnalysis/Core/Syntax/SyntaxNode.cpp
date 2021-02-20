#include "CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxNode::SyntaxNode() noexcept
    : ISyntaxNode{},
      _position{},
      _fullWidth{},
      _syntaxKind{SyntaxKind::None},
      _flags{SyntaxNodeFlags::None},
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
      _flags{SyntaxNodeFlags::None},
      _pParent{parent}
{}

SyntaxNode::~SyntaxNode() noexcept
{}

bool SyntaxNode::hasMissingTokens() const noexcept
{
    for (pg_size i = 0; i < childCount(); i++)
    {
        ISyntaxNode* pChild = child(i);

        if (pChild != nullptr && pChild->isMissing())
            return true;
    }

    return false;
}

pg_size SyntaxNode::leadingTriviaWidth() const noexcept
{
    if (_fullWidth != 0)
    {
        ISyntaxNode* pFirstTerminal = firstTerminal();

        if (pFirstTerminal != nullptr)
            return pFirstTerminal->leadingTriviaWidth();
    }

    return 0;
}

pg_size SyntaxNode::trailingTriviaWidth() const noexcept
{
    if (_fullWidth != 0)
    {
        ISyntaxNode* pLastTerminal = lastTerminal();

        if (pLastTerminal != nullptr)
            return pLastTerminal->trailingTriviaWidth();
    }

    return 0;
}

ISyntaxToken* SyntaxNode::firstToken() const noexcept
{
    return dynamic_cast<ISyntaxToken*>(firstTerminal());
}

ISyntaxToken* SyntaxNode::lastToken() const noexcept
{
    return dynamic_cast<ISyntaxToken*>(lastTerminal());
}

void SyntaxNode::adjustWidthAndFlags(ISyntaxNode* node) noexcept
{
    if (node != nullptr)
    {
        SyntaxNode* pSyntaxNode = dynamic_cast<SyntaxNode*>(node);

        _fullWidth += pSyntaxNode->_fullWidth;
        _flags |= pSyntaxNode->_flags;
    }
}

ISyntaxNode* SyntaxNode::firstTerminal() const noexcept
{
    ISyntaxNode* pNode = const_cast<SyntaxNode*>(this);

    do
    {
        ISyntaxNode* pFirstChild{nullptr};

        for (pg_size i = 0, n = pNode->childCount(); i < n; i++)
        {
            ISyntaxNode* pChild = pNode->child(i);

            if (pChild != nullptr)
            {
                pFirstChild = pChild;
                break;
            }
        }

        pNode = pFirstChild;
    }
    while (pNode != nullptr && pNode->childCount() > 0);

    return pNode;
}

ISyntaxNode* SyntaxNode::lastTerminal() const noexcept
{
    ISyntaxNode* pNode = const_cast<SyntaxNode*>(this);

    do
    {
        ISyntaxNode* pLastChild{nullptr};

        for (pg_size i = pNode->childCount() - 1; i > -1; i--)
        {
            ISyntaxNode* pChild = pNode->child(i);

            if (pChild != nullptr)
            {
                pLastChild = pChild;
                break;
            }
        }

        pNode = pLastChild;
    }
    while (pNode != nullptr && pNode->childCount() > 0);

    return pNode;
}

} // end namespace polyglot::CodeAnalysis
