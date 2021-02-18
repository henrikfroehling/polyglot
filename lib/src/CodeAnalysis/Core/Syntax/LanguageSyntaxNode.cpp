#include "CodeAnalysis/Core/Syntax/LanguageSyntaxNode.hpp"
//#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

//LanguageSyntaxNode::LanguageSyntaxNode() noexcept
//    : _position{},
//      _fullWidth{},
//      _syntaxKind{SyntaxKind::None},
//      _flags{SyntaxNodeFlags::None}
//{}
//
//LanguageSyntaxNode::LanguageSyntaxNode(SyntaxKind syntaxKind,
//                                       pg_size position,
//                                       pg_size fullWidth) noexcept
//    : _position{position},
//      _fullWidth{fullWidth},
//      _syntaxKind{syntaxKind},
//      _flags{SyntaxNodeFlags::None}
//{}
//
//LanguageSyntaxNode::~LanguageSyntaxNode() noexcept
//{}
//
//pg_size LanguageSyntaxNode::leadingTriviaWidth() const noexcept
//{
//    if (_fullWidth != 0)
//    {
//        LanguageSyntaxNode* pFirstTerminal = firstTerminal();
//
//        if (pFirstTerminal != nullptr)
//            return pFirstTerminal->leadingTriviaWidth();
//    }
//
//    return 0;
//}
//
//pg_size LanguageSyntaxNode::trailingTriviaWidth() const noexcept
//{
//    if (_fullWidth != 0)
//    {
//        LanguageSyntaxNode* pLastTerminal = lastTerminal();
//
//        if (pLastTerminal != nullptr)
//            return pLastTerminal->trailingTriviaWidth();
//    }
//
//    return 0;
//}
//
//LanguageSyntaxToken* LanguageSyntaxNode::firstToken() const noexcept
//{
//    return static_cast<LanguageSyntaxToken*>(firstTerminal());
//}
//
//LanguageSyntaxToken* LanguageSyntaxNode::lastToken() const noexcept
//{
//    return static_cast<LanguageSyntaxToken*>(lastTerminal());
//}
//
//void LanguageSyntaxNode::adjustWidthAndFlags(LanguageSyntaxNode* node) noexcept
//{
//    if (node != nullptr)
//    {
//        _fullWidth += node->_fullWidth;
//        _flags |= node->_flags;
//    }
//}
//
//LanguageSyntaxNode* LanguageSyntaxNode::firstTerminal() const noexcept
//{
//    LanguageSyntaxNode* pNode = const_cast<LanguageSyntaxNode*>(this);
//
//    do
//    {
//        LanguageSyntaxNode* pFirstChild{nullptr};
//
//        for (pg_size i = 0, n = pNode->childCount(); i < n; i++)
//        {
//            LanguageSyntaxNode* pChild = pNode->child(i);
//
//            if (pChild != nullptr)
//            {
//                pFirstChild = pChild;
//                break;
//            }
//        }
//
//        pNode = pFirstChild;
//    }
//    while (pNode != nullptr && pNode->childCount() > 0);
//
//    return pNode;
//}
//
//LanguageSyntaxNode* LanguageSyntaxNode::lastTerminal() const noexcept
//{
//    LanguageSyntaxNode* pNode = const_cast<LanguageSyntaxNode*>(this);
//
//    do
//    {
//        LanguageSyntaxNode* pLastChild{nullptr};
//
//        for (pg_size i = pNode->childCount() - 1; i > -1; i--)
//        {
//            LanguageSyntaxNode* pChild = pNode->child(i);
//
//            if (pChild != nullptr)
//            {
//                pLastChild = pChild;
//                break;
//            }
//        }
//
//        pNode = pLastChild;
//    }
//    while (pNode != nullptr && pNode->childCount() > 0);
//
//    return pNode;
//}

} // end namespace polyglot::CodeAnalysis
