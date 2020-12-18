#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxNode::SyntaxNode() noexcept
    : _syntaxKind{SyntaxKind::None},
      _position{},
      _flags{SyntaxNodeFlags::None}
{}

SyntaxNode::~SyntaxNode() noexcept
{}

SyntaxNode::SyntaxNode(SyntaxKind syntaxKind) noexcept
    : _syntaxKind{syntaxKind},
      _position{},
      _flags{SyntaxNodeFlags::None}
{}

SyntaxNode::SyntaxNode(SyntaxKind syntaxKind,
                       pg_size position) noexcept
    : _syntaxKind{syntaxKind},
      _position{position},
      _flags{SyntaxNodeFlags::None}
{}

} // end namespace polyglot::CodeAnalysis
