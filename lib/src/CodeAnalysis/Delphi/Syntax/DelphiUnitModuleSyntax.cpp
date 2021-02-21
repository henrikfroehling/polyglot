#include "CodeAnalysis/Delphi/Syntax/DelphiUnitModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiEndOfModuleSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiUnitFinalizationSectionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiUnitHeadSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiUnitImplementationSectionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiUnitInitializationSectionSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiUnitInterfaceSectionSyntax.hpp"
#include <cassert>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

DelphiUnitModuleSyntax::DelphiUnitModuleSyntax(DelphiUnitHeadSyntax* head,
                                               DelphiUnitInterfaceSectionSyntax* interfaceSection,
                                               DelphiUnitImplementationSectionSyntax* implementationSection,
                                               DelphiEndOfModuleSyntax* endOfModule,
                                               ISyntaxToken* EOFToken,
                                               DelphiUnitInitializationSectionSyntax* initializationSection,
                                               DelphiUnitFinalizationSectionSyntax* finalizationSection) noexcept
    : DelphiCompilationUnitSyntax{SyntaxKind::UnitModule, EOFToken},
      _pHead{head},
      _pInterfaceSection{interfaceSection},
      _pImplementationSection{implementationSection},
      _pInitializationSection{initializationSection},
      _pFinalizationSection{finalizationSection},
      _pEndOfModule{endOfModule}
{
    _position = _pHead->position();
    adjustWidthAndFlags(_pHead);
    _pHead->setChildNumber(0);
    adjustWidthAndFlags(_pInterfaceSection);
    _pInterfaceSection->setChildNumber(1);
    adjustWidthAndFlags(_pImplementationSection);
    _pImplementationSection->setChildNumber(2);

    pg_size childNr{3};

    if (_pInitializationSection != nullptr)
    {
        adjustWidthAndFlags(_pInitializationSection);
        _pInitializationSection->setChildNumber(childNr++);
    }

    if (_pFinalizationSection != nullptr)
    {
        assert(_pInitializationSection != nullptr);
        adjustWidthAndFlags(_pFinalizationSection);
        _pFinalizationSection->setChildNumber(childNr++);
    }

    adjustWidthAndFlags(_pEndOfModule);
    _pEndOfModule->setChildNumber(childNr++);
    adjustWidthAndFlags(_pEOFToken);
    _pEOFToken->setChildNumber(childNr++);
}

ISyntaxNode* DelphiUnitModuleSyntax::child(pg_size index) const
{
    switch (childCount())
    {
        case 5:
        {
            switch (index)
            {
                case 0: return _pHead;
                case 1: return _pInterfaceSection;
                case 2: return _pImplementationSection;
                case 3: return _pEndOfModule;
                case 4: return _pEOFToken;
            }
        }
        case 6:
        {
            switch (index)
            {
                case 0: return _pHead;
                case 1: return _pInterfaceSection;
                case 2: return _pImplementationSection;
                case 3: return _pInitializationSection;
                case 4: return _pEndOfModule;
                case 5: return _pEOFToken;
            }
        }
        case 7:
        {
            switch (index)
            {
                case 0: return _pHead;
                case 1: return _pInterfaceSection;
                case 2: return _pImplementationSection;
                case 3: return _pInitializationSection;
                case 4: return _pFinalizationSection;
                case 5: return _pEndOfModule;
                case 6: return _pEOFToken;
            }
        }
    }

    throw std::out_of_range{"index out of range"};
}

pg_size DelphiUnitModuleSyntax::childCount() const noexcept
{
    pg_size count{5};

    if (_pInitializationSection != nullptr)
        count++;

    if (_pFinalizationSection != nullptr)
        count++;

    return count;
}

DelphiUnitModuleSyntax* DelphiUnitModuleSyntax::create(SyntaxFactory& syntaxFactory,
                                                       DelphiUnitHeadSyntax* head,
                                                       DelphiUnitInterfaceSectionSyntax* interfaceSection,
                                                       DelphiUnitImplementationSectionSyntax* implementationSection,
                                                       DelphiEndOfModuleSyntax* endOfModule,
                                                       ISyntaxToken* EOFToken,
                                                       DelphiUnitInitializationSectionSyntax* initializationSection,
                                                       DelphiUnitFinalizationSectionSyntax* finalizationSection) noexcept
{
    assert(head != nullptr);
    assert(head->syntaxKind() == SyntaxKind::UnitHead);
    assert(interfaceSection != nullptr);
    assert(interfaceSection->syntaxKind() == SyntaxKind::UnitInterfaceSection);
    assert(implementationSection != nullptr);
    assert(implementationSection->syntaxKind() == SyntaxKind::UnitImplementationSection);
    assert(endOfModule != nullptr);
    assert(endOfModule->syntaxKind() == SyntaxKind::EndOfModule);
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
                                                                        endOfModule, EOFToken,
                                                                        initializationSection, finalizationSection);

    return dynamic_cast<DelphiUnitModuleSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrUnitModuleSyntax)));
}

} // end namespace polyglot::CodeAnalysis
