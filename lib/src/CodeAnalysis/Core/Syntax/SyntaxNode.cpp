#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

SyntaxNode::SyntaxNode() noexcept
    : _syntaxKind{SyntaxKind::None},
      _position{},
      _flags{SyntaxNodeFlags::None},
      _fullWidth{},
      _pParent{nullptr}
{}

SyntaxNode::~SyntaxNode() noexcept
{}

SyntaxNode::SyntaxNode(SyntaxKind syntaxKind) noexcept
    : _syntaxKind{syntaxKind},
      _position{},
      _flags{SyntaxNodeFlags::None},
      _fullWidth{},
      _pParent{nullptr}
{}

SyntaxNode::SyntaxNode(SyntaxKind syntaxKind,
                       pg_size position) noexcept
    : _syntaxKind{syntaxKind},
      _position{position},
      _flags{SyntaxNodeFlags::None},
      _fullWidth{},
      _pParent{nullptr}
{}

TextSpan SyntaxNode::span() const noexcept
{
    pg_size start = _position;
    pg_size width = _fullWidth;
    const pg_size leadingWidth = leadingTriviaWidth();
    start += leadingWidth;
    width -= leadingWidth;
    width -= trailingTriviaWidth();
    assert(width >= 0);
    return TextSpan{start, width};
}

pg_size SyntaxNode::leadingTriviaWidth() const noexcept
{
    if (_fullWidth != 0)
    {
        SyntaxNode* pFirstTerminal = firstTerminal();

        if (pFirstTerminal != nullptr)
            return pFirstTerminal->leadingTriviaWidth();
    }

    return 0;
}

pg_size SyntaxNode::trailingTriviaWidth() const noexcept
{
    if (_fullWidth != 0)
    {
        SyntaxNode* pLastTerminal = lastTerminal();

        if (pLastTerminal != nullptr)
            return pLastTerminal->trailingTriviaWidth();
    }

    return 0;
}

SyntaxNode* SyntaxNode::firstTerminal() const noexcept
{
    SyntaxNode* pNode = const_cast<SyntaxNode*>(this);

    if (childCount() > 0)
    {
        do
        {
            SyntaxNode* pFirstChild{ nullptr };

            for (pg_size i = 0, n = pNode->childCount(); i < n; i++)
            {
                SyntaxNode* pChild = child(i);

                if (pChild != nullptr)
                {
                    pFirstChild = pChild;
                    break;
                }
            }

            pNode = pFirstChild;
        }
        while (pNode != nullptr && pNode->childCount() > 0);
    }

    return pNode;
}

SyntaxNode* SyntaxNode::lastTerminal() const noexcept
{
    SyntaxNode* pNode = const_cast<SyntaxNode*>(this);

    if (childCount() > 0)
    {
        do
        {
            SyntaxNode* pLastChild{ nullptr };

            for (pg_size i = pNode->childCount() - 1; i > -1; i--)
            {
                SyntaxNode* pChild = child(i);

                if (pChild != nullptr)
                {
                    pLastChild = pChild;
                    break;
                }
            }

            pNode = pLastChild;
        }
        while (pNode != nullptr && pNode->childCount() > 0);
    }

    return pNode;
}

} // end namespace polyglot::CodeAnalysis
