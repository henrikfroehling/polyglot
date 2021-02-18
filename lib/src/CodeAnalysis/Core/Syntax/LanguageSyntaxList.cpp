#include "CodeAnalysis/Core/Syntax/LanguageSyntaxList.hpp"
//#include <cassert>

namespace polyglot::CodeAnalysis
{

//LanguageSyntaxList::LanguageSyntaxList() noexcept
//    : LanguageSyntaxNode{SyntaxKind::SyntaxList},
//      _children{}
//{}
//
//LanguageSyntaxList::LanguageSyntaxList(std::vector<LanguageSyntaxNode*>&& children) noexcept
//    : LanguageSyntaxNode{SyntaxKind::SyntaxList},
//      _children{std::move(children)}
//{
//    if (_children.size() > 0)
//        _position = _children[0]->position();
//
//    for (LanguageSyntaxNode* child : _children)
//        adjustWidthAndFlags(child);
//}
//
//LanguageSyntaxList::~LanguageSyntaxList() noexcept
//{}
//
//void LanguageSyntaxList::add(LanguageSyntaxNode* node) noexcept
//{
//    assert(node != nullptr);
//
//    if (_children.empty())
//        _position = node->position();
//
//    _children.push_back(node);
//    adjustWidthAndFlags(node);
//}

} // end namespace polyglot::CodeAnalysis
