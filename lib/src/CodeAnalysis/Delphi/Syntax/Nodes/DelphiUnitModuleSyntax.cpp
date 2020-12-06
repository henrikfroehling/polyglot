#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitModuleSyntax::DelphiUnitModuleSyntax(Ptr<DelphiUnitHeadingSyntax> heading,
                                               Ptr<DelphiUnitInterfaceSectionSyntax> interfaceSection,
                                               Ptr<DelphiUnitImplementationSectionSyntax> implementationSection,
                                               Ptr<SyntaxToken> endKeyword,
                                               Ptr<SyntaxToken> dotToken) noexcept
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
