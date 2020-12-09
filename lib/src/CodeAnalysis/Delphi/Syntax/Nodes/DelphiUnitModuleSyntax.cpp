#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitModuleSyntax::DelphiUnitModuleSyntax(DelphiUnitHeadingSyntax* heading,
                                               DelphiUnitInterfaceSectionSyntax* interfaceSection,
                                               DelphiUnitImplementationSectionSyntax* implementationSection,
                                               SyntaxToken* endKeyword,
                                               SyntaxToken* dotToken) noexcept
    : DelphiCompilationUnitSyntax{SyntaxKind::UnitModule},
      _ptrHeading{heading},
      _ptrInterfaceSection{interfaceSection},
      _ptrImplementationSection{implementationSection},
      _ptrInitializationSection{nullptr},
      _ptrFinalizationSection{nullptr},
      _ptrEndKeyword{endKeyword},
      _ptrDotToken{dotToken}
{}

} // end namespace polyglot::CodeAnalysis
