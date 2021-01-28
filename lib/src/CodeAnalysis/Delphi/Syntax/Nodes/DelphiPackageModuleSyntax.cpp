#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageHeadingSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageRequiresClauseSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageContainsClauseSyntax.hpp"

namespace polyglot::CodeAnalysis
{

DelphiPackageModuleSyntax::DelphiPackageModuleSyntax() noexcept
    : DelphiCompilationUnitSyntax{SyntaxKind::PackageModule},
      _pHeading{nullptr},
      _pRequiresClause{nullptr},
      _pContainsClause{nullptr}
{}

void DelphiPackageModuleSyntax::setHeading(DelphiPackageHeadingSyntax* heading) noexcept
{
    _pHeading = heading;
    adjustWidthAndFlags(_pHeading);
}

void DelphiPackageModuleSyntax::setRequiresClause(DelphiPackageRequiresClauseSyntax* requiresClause) noexcept
{
    _pRequiresClause = requiresClause;
    adjustWidthAndFlags(_pRequiresClause);
}

void DelphiPackageModuleSyntax::setContainsClause(DelphiPackageContainsClauseSyntax* containsClause) noexcept
{
    _pContainsClause = containsClause;
    adjustWidthAndFlags(_pContainsClause);
}

} // end namespace polyglot::CodeAnalysis
