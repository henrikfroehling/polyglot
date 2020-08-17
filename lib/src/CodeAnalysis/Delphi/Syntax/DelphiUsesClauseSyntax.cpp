#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUsesClauseSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUsesClauseSyntax::DelphiUsesClauseSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::UsesClause}
{}

} // end namespace polyglot::CodeAnalysis
