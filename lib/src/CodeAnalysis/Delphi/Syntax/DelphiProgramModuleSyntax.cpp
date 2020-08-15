#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiProgramModuleSyntax.hpp"

namespace polyglot::CodeAnalysis
{

DelphiProgramModuleSyntax::DelphiProgramModuleSyntax(SyntaxKind syntaxKind) noexcept
    : DelphiCompilationUnitSyntax{syntaxKind}
{}

} // end namespace polyglot::CodeAnalysis
