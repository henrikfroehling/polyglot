#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiUnitHeadSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Expressions/DelphiEndOfModuleExpressionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitFinalizationSectionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitImplementationSectionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInitializationSectionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInterfaceSectionSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

DelphiUnitModuleSyntax::DelphiUnitModuleSyntax(DelphiUnitHeadSyntax* head,
                                               DelphiUnitInterfaceSectionSyntax* interfaceSection,
                                               DelphiUnitImplementationSectionSyntax* implementationSection,
                                               DelphiEndOfModuleExpressionSyntax* endOfModuleExpression,
                                               LanguageSyntaxToken* EOFToken,
                                               DelphiUnitInitializationSectionSyntax* initializationSection,
                                               DelphiUnitFinalizationSectionSyntax* finalizationSection) noexcept
    : DelphiCompilationUnitSyntax{SyntaxKind::UnitModule, EOFToken},
      _pHead{head},
      _pInterfaceSection{interfaceSection},
      _pImplementationSection{implementationSection},
      _pInitializationSection{initializationSection},
      _pFinalizationSection{finalizationSection},
      _pEndOfModuleExpression{endOfModuleExpression}
{
    _position = _pHead->position();
    adjustWidthAndFlags(_pHead);
    adjustWidthAndFlags(_pInterfaceSection);
    adjustWidthAndFlags(_pImplementationSection);
    adjustWidthAndFlags(_pEndOfModuleExpression);

    if (_pInitializationSection != nullptr)
        adjustWidthAndFlags(_pInitializationSection);

    if (_pFinalizationSection != nullptr)
        adjustWidthAndFlags(_pFinalizationSection);
}

DelphiUnitModuleSyntax* DelphiUnitModuleSyntax::create(SyntaxFactory& syntaxFactory,
                                                       DelphiUnitHeadSyntax* head,
                                                       DelphiUnitInterfaceSectionSyntax* interfaceSection,
                                                       DelphiUnitImplementationSectionSyntax* implementationSection,
                                                       DelphiEndOfModuleExpressionSyntax* endOfModuleExpression,
                                                       LanguageSyntaxToken* EOFToken,
                                                       DelphiUnitInitializationSectionSyntax* initializationSection,
                                                       DelphiUnitFinalizationSectionSyntax* finalizationSection) noexcept
{
    assert(head != nullptr);
    assert(head->syntaxKind() == SyntaxKind::UnitHead);
    assert(interfaceSection != nullptr);
    assert(interfaceSection->syntaxKind() == SyntaxKind::UnitInterfaceSection);
    assert(implementationSection != nullptr);
    assert(implementationSection->syntaxKind() == SyntaxKind::UnitImplementationSection);
    assert(endOfModuleExpression != nullptr);
    assert(endOfModuleExpression->syntaxKind() == SyntaxKind::EndOfModuleExpression);
    assert(EOFToken != nullptr);
    assert(EOFToken->syntaxKind() == SyntaxKind::EndOfFileToken);

    if (initializationSection != nullptr)
        assert(initializationSection->syntaxKind() == SyntaxKind::UnitInitializationSection);

    if (finalizationSection != nullptr)
    {
        assert(initializationSection != nullptr);
        assert(finalizationSection->syntaxKind() == SyntaxKind::UnitFinalizationSection);
    }

    auto ptrUnitModuleSyntax = std::make_unique<DelphiUnitModuleSyntax>(head, interfaceSection, implementationSection,
                                                                        endOfModuleExpression, EOFToken,
                                                                        initializationSection, finalizationSection);

    return static_cast<DelphiUnitModuleSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrUnitModuleSyntax)));
}

} // end namespace polyglot::CodeAnalysis
