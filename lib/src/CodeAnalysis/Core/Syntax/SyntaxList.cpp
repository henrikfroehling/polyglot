#include "CodeAnalysis/Core/Syntax/SyntaxList.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxNode.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

SyntaxList::SyntaxList() noexcept
    : SyntaxNode{SyntaxKind::SyntaxList},
      _children{}
{}

SyntaxList::SyntaxList(std::vector<ISyntaxNode*>&& children) noexcept
    : SyntaxNode{SyntaxKind::SyntaxList},
      _children{std::move(children)}
{
    if (_children.size() > 0)
        _position = _children[0]->position();

    for (ISyntaxNode* pChild : _children)
        adjustWidthAndFlags(pChild);
}

SyntaxList::~SyntaxList() noexcept
{}

void SyntaxList::add(ISyntaxNode* node) noexcept
{
    assert(node != nullptr);

    if (_children.empty())
        _position = node->position();

    _children.push_back(node);
    adjustWidthAndFlags(node);
}

} // end namespace polyglot::CodeAnalysis
