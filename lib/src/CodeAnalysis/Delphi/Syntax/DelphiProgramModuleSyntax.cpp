#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiProgramModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiProgramModuleSyntax::DelphiProgramModuleSyntax() noexcept
    : DelphiCompilationUnitSyntax{SyntaxKind::ProgramModule},
      _ptrHeading{nullptr},
      _ptrUses{nullptr}
{}

} // end namespace polyglot::CodeAnalysis
