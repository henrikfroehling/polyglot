#include "DelphiSyntaxNode.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiSyntaxNode::DelphiSyntaxNode(Core::Syntax::SyntaxKind syntaxKind) noexcept
    : Core::Syntax::SyntaxNode{syntaxKind}
{}

} // end namespace polyglot::Delphi::Syntax
