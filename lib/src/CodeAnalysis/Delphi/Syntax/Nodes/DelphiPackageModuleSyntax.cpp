#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiPackageModuleSyntax::DelphiPackageModuleSyntax() noexcept
    : DelphiCompilationUnitSyntax{SyntaxKind::PackageModule},
      _pHeading{nullptr},
      _pRequiresClause{nullptr},
      _pContainsClause{nullptr}
{}

} // end namespace polyglot::CodeAnalysis
