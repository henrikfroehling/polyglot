#include "DelphiPackageRequiresClauseSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiPackageRequiresClauseSyntax::DelphiPackageRequiresClauseSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::PackageRequiresClause}
{}

} // end namespace polyglot::Delphi::Syntax
