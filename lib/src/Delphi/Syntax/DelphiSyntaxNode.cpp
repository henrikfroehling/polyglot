#include "DelphiSyntaxNode.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiSyntaxNode::DelphiSyntaxNode(SyntaxKind syntaxKind) noexcept
    : SyntaxNode{syntaxKind}
{}

} // end namespace polyglot::Delphi::Syntax
