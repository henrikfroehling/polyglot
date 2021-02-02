#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageRequiresClauseSyntax.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiPackageRequiresClauseSyntax::DelphiPackageRequiresClauseSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::PackageRequiresClause}
{}

} // end namespace polyglot::CodeAnalysis
