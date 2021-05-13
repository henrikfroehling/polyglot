#include "Delphi/Syntax/DelphiPackageContainsClauseSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiPackageContainsClauseSyntax::DelphiPackageContainsClauseSyntax() noexcept
    : DelphiSyntaxNode{Core::Syntax::SyntaxKind::PackageContainsClause}
{}

} // end namespace polyglot::Delphi::Syntax
