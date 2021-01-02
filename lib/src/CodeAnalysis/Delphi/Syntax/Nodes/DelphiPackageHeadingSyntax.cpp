#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageHeadingSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiPackageHeadingSyntax::DelphiPackageHeadingSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::PackageHeading}
{}

} // end namespace polyglot::CodeAnalysis
