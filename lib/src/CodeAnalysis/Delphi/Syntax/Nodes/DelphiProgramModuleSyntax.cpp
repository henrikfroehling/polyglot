#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiProgramModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiProgramHeadingSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.hpp"

namespace polyglot::CodeAnalysis
{

DelphiProgramModuleSyntax::DelphiProgramModuleSyntax() noexcept
    : DelphiCompilationUnitSyntax{SyntaxKind::ProgramModule},
      _pHeading{nullptr},
      _pUses{nullptr}
{}

void DelphiProgramModuleSyntax::setHeading(DelphiProgramHeadingSyntax* heading) noexcept
{
    _pHeading = heading;
    adjustWidthAndFlags(_pHeading);
}

void DelphiProgramModuleSyntax::setUses(DelphiUsesClauseSyntax* uses) noexcept
{
    _pUses = uses;
    adjustWidthAndFlags(_pUses);
}

} // end namespace polyglot::CodeAnalysis
