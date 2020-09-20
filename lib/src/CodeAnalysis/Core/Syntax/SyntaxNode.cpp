#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxNode::SyntaxNode() noexcept
    : _syntaxKind{SyntaxKind::None},
      _position{}
{}

SyntaxNode::~SyntaxNode() noexcept
{}

SyntaxNode::SyntaxNode(SyntaxKind syntaxKind) noexcept
    : _syntaxKind{syntaxKind},
      _position{}
{}

SyntaxNode::SyntaxNode(SyntaxKind syntaxKind,
                       pg_size position) noexcept
    : _syntaxKind{syntaxKind},
      _position{position}
{}

} // end namespace polyglot::CodeAnalysis
