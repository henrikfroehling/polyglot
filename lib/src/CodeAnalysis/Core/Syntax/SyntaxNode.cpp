#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

SyntaxNode::SyntaxNode(SyntaxKind syntaxKind) noexcept
    : _syntaxKind{syntaxKind}
{}

} // end namespace polyglot::CodeAnalysis
