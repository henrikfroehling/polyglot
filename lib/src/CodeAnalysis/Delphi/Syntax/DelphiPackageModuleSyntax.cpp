#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiPackageModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiPackageModuleSyntax::DelphiPackageModuleSyntax() noexcept
    : DelphiCompilationUnitSyntax{SyntaxKind::PackageModule},
      _ptrHeading{nullptr},
      _ptrRequiresClause{nullptr},
      _ptrContainsClause{nullptr}
{}

} // end namespace polyglot::CodeAnalysis
