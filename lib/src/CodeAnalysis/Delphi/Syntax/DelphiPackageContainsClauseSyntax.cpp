#include "CodeAnalysis/Delphi/Syntax/DelphiPackageContainsClauseSyntax.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiPackageContainsClauseSyntax::DelphiPackageContainsClauseSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::PackageContainsClause}
{}

} // end namespace polyglot::CodeAnalysis
