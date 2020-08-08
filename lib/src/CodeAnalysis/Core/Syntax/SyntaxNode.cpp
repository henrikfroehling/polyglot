#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxNode::SyntaxNode() noexcept
    : _syntaxKind{SyntaxKind::None}
{}

SyntaxNode::~SyntaxNode() noexcept
{}

SyntaxNode::SyntaxNode(SyntaxKind syntaxKind) noexcept
    : _syntaxKind{syntaxKind}
{}

SyntaxNode::SyntaxNode(SyntaxKind syntaxKind,
                       pg_size position) noexcept
    : _syntaxKind{syntaxKind}
{}

} // end namespace polyglot::CodeAnalysis
