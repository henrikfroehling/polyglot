#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiPackageModuleSyntax.hpp"

namespace polyglot::CodeAnalysis
{

DelphiPackageModuleSyntax::DelphiPackageModuleSyntax(SyntaxKind syntaxKind) noexcept
    : DelphiCompilationUnitSyntax{syntaxKind}
{}

} // end namespace polyglot::CodeAnalysis
