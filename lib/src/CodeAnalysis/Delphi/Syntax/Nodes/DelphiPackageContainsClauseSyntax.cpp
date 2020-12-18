#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageContainsClauseSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiPackageContainsClauseSyntax::DelphiPackageContainsClauseSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::PackageContainsClause}
{}

} // end namespace polyglot::CodeAnalysis
