#include "DelphiPackageRequiresClauseSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiPackageRequiresClauseSyntax::DelphiPackageRequiresClauseSyntax() noexcept
    : DelphiSyntaxNode{Core::Syntax::SyntaxKind::PackageRequiresClause}
{}

} // end namespace polyglot::Delphi::Syntax
