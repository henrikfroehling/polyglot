#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitFinalizationSectionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitHeadingSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitImplementationSectionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInitializationSectionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInterfaceSectionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitModuleSyntax::DelphiUnitModuleSyntax(DelphiUnitHeadingSyntax* heading,
                                               DelphiUnitInterfaceSectionSyntax* interfaceSection,
                                               DelphiUnitImplementationSectionSyntax* implementationSection,
                                               LanguageSyntaxToken* endKeyword,
                                               LanguageSyntaxToken* dotToken) noexcept
    : DelphiCompilationUnitSyntax{SyntaxKind::UnitModule},
      _pHeading{heading},
      _pInterfaceSection{interfaceSection},
      _pImplementationSection{implementationSection},
      _pInitializationSection{nullptr},
      _pFinalizationSection{nullptr},
      _pEndKeyword{endKeyword},
      _pDotToken{dotToken}
{
    adjustWidthAndFlags(_pHeading);
    adjustWidthAndFlags(_pInterfaceSection);
    adjustWidthAndFlags(_pImplementationSection);
    adjustWidthAndFlags(_pEndKeyword);
    adjustWidthAndFlags(_pDotToken);
}

void DelphiUnitModuleSyntax::setInitializationSection(DelphiUnitInitializationSectionSyntax* initializationSection) noexcept
{
    _pInitializationSection = initializationSection;
    adjustWidthAndFlags(_pInitializationSection);
}

void DelphiUnitModuleSyntax::setFinalizationSection(DelphiUnitFinalizationSectionSyntax* finalizationSection) noexcept
{
    _pFinalizationSection = finalizationSection;
    adjustWidthAndFlags(_pFinalizationSection);
}

} // end namespace polyglot::CodeAnalysis
