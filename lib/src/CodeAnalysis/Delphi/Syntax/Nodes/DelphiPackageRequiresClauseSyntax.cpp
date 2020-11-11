#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageRequiresClauseSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiPackageRequiresClauseSyntax::DelphiPackageRequiresClauseSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::PackageRequiresClause}
{}

} // end namespace polyglot::CodeAnalysis
