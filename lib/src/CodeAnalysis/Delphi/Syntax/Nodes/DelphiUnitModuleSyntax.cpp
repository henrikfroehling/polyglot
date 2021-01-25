#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitModuleSyntax::DelphiUnitModuleSyntax(DelphiUnitHeadingSyntax* heading,
                                               DelphiUnitInterfaceSectionSyntax* interfaceSection,
                                               DelphiUnitImplementationSectionSyntax* implementationSection,
                                               SyntaxToken* endKeyword,
                                               SyntaxToken* dotToken) noexcept
    : DelphiCompilationUnitSyntax{SyntaxKind::UnitModule},
      _pHeading{heading},
      _pInterfaceSection{interfaceSection},
      _pImplementationSection{implementationSection},
      _pInitializationSection{nullptr},
      _pFinalizationSection{nullptr},
      _pEndKeyword{endKeyword},
      _pDotToken{dotToken}
{}

} // end namespace polyglot::CodeAnalysis
