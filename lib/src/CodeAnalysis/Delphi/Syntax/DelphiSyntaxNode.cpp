#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

DelphiSyntaxNode::DelphiSyntaxNode(SyntaxKind syntaxKind) noexcept
    : LanguageSyntaxNode{syntaxKind}
{}

} // end namespace polyglot::CodeAnalysis
