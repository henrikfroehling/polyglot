#include "DelphiPackageHeadSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiPackageHeadSyntax::DelphiPackageHeadSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::PackageHead}
{}

} // end namespace polyglot::Delphi::Syntax
