#include "CodeAnalysis/Delphi/Syntax/DelphiPackageHeadSyntax.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiPackageHeadSyntax::DelphiPackageHeadSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::PackageHead}
{}

} // end namespace polyglot::CodeAnalysis
