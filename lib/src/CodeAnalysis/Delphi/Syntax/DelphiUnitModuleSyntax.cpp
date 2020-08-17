#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitModuleSyntax::DelphiUnitModuleSyntax(DelphiUnitHeadingSyntaxPtr heading,
                                               DelphiUnitInterfaceSectionSyntaxPtr interfaceSection,
                                               DelphiUnitImplementationSectionSyntaxPtr implementationSection,
                                               SyntaxTokenPtr endKeyword,
                                               SyntaxTokenPtr dotToken) noexcept
    : DelphiCompilationUnitSyntax{SyntaxKind::UnitModule},
      _ptrHeading{std::move(heading)},
      _ptrInterfaceSection{std::move(interfaceSection)},
      _ptrImplementationSection{std::move(implementationSection)},
      _ptrInitializationSection{nullptr},
      _ptrFinalizationSection{nullptr},
      _ptrEndKeyword{std::move(endKeyword)},
      _ptrDotToken{std::move(dotToken)}
{}

} // end namespace polyglot::CodeAnalysis
