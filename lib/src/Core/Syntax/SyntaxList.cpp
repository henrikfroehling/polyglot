#include "SyntaxList.hpp"

namespace polyglot::Core::Syntax
{

SyntaxList::SyntaxList(std::vector<SyntaxNodeOrToken>&& children) noexcept
    : ISyntaxList{},
      SyntaxNode{SyntaxKind::SyntaxList},
      _children{std::move(children)}
{
    if (_children.size() > 0)
        _position = _children[0]->position();

    for (SyntaxNodeOrToken& child : _children)
    {
        if (child.isNode())
            adjustWidthAndFlags(child.node);
        else if (child.isToken())
            adjustWidthAndFlags(child.token);
    }
}

} // end namespace polyglot::Core::Syntax
