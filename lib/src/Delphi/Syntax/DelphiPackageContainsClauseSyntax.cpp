#include "DelphiPackageContainsClauseSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiPackageContainsClauseSyntax::DelphiPackageContainsClauseSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::PackageContainsClause}
{}

} // end namespace polyglot::Delphi::Syntax
