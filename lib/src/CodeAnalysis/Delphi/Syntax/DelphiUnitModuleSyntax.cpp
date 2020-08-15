#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitModuleSyntax.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitModuleSyntax::DelphiUnitModuleSyntax(SyntaxKind syntaxKind) noexcept
    : DelphiCompilationUnitSyntax{syntaxKind},
      _ptrInterfaceSection{nullptr},
      _ptrImplementationSection{nullptr},
      _ptrInitializationSection{nullptr},
      _ptrFinalizationSection{nullptr}
{}

} // end namespace polyglot::CodeAnalysis
