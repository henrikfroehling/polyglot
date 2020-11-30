#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitModuleSyntax::DelphiUnitModuleSyntax(SharedPtr<DelphiUnitHeadingSyntax> heading,
                                               SharedPtr<DelphiUnitInterfaceSectionSyntax> interfaceSection,
                                               SharedPtr<DelphiUnitImplementationSectionSyntax> implementationSection,
                                               SharedPtr<SyntaxToken> endKeyword,
                                               SharedPtr<SyntaxToken> dotToken) noexcept
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
