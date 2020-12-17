#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiProgramModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiProgramModuleSyntax::DelphiProgramModuleSyntax() noexcept
    : DelphiCompilationUnitSyntax{SyntaxKind::ProgramModule},
      _pHeading{nullptr},
      _pUses{nullptr}
{}

} // end namespace polyglot::CodeAnalysis
