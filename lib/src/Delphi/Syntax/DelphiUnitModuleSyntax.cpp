#include "Delphi/Syntax/DelphiUnitModuleSyntax.hpp"
#include <cassert>
#include <sstream>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/DelphiUnitFinalizationSectionSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitHeadSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitImplementationSectionSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitInitializationSectionSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitInterfaceSectionSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::ISyntaxToken;
using Core::Syntax::SyntaxFactory;
using Core::Syntax::SyntaxKind;
using Core::Syntax::SyntaxVariant;

DelphiUnitModuleSyntax::DelphiUnitModuleSyntax(DelphiUnitHeadSyntax* head,
                                               DelphiUnitInterfaceSectionSyntax* interfaceSection,
                                               DelphiUnitImplementationSectionSyntax* implementationSection,
                                               DelphiEndOfModuleExpressionSyntax* endOfModule,
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
    adjustWidthAndFlags(_pInterfaceSection);
    adjustWidthAndFlags(_pImplementationSection);

    if (_pInitializationSection != nullptr)
        adjustWidthAndFlags(_pInitializationSection);

    if (_pFinalizationSection != nullptr)
    {
        assert(_pInitializationSection != nullptr);
        adjustWidthAndFlags(_pFinalizationSection);
    }

    adjustWidthAndFlags(_pEndOfModule);
    adjustWidthAndFlags(_pEOFToken);
}

SyntaxVariant DelphiUnitModuleSyntax::child(pg_size index) const
{
    switch (childCount())
    {
        case 5:
        {
            switch (index)
            {
                case 0: return SyntaxVariant::asNode(_pHead);
                case 1: return SyntaxVariant::asNode(_pInterfaceSection);
                case 2: return SyntaxVariant::asNode(_pImplementationSection);
                case 3: return SyntaxVariant::asNode(_pEndOfModule);
                case 4: return SyntaxVariant::asToken(_pEOFToken);
            }
        }
        case 6:
        {
            switch (index)
            {
                case 0: return SyntaxVariant::asNode(_pHead);
                case 1: return SyntaxVariant::asNode(_pInterfaceSection);
                case 2: return SyntaxVariant::asNode(_pImplementationSection);
                case 3: return SyntaxVariant::asNode(_pInitializationSection);
                case 4: return SyntaxVariant::asNode(_pEndOfModule);
                case 5: return SyntaxVariant::asToken(_pEOFToken);
            }
        }
        case 7:
        {
            switch (index)
            {
                case 0: return SyntaxVariant::asNode(_pHead);
                case 1: return SyntaxVariant::asNode(_pInterfaceSection);
                case 2: return SyntaxVariant::asNode(_pImplementationSection);
                case 3: return SyntaxVariant::asNode(_pInitializationSection);
                case 4: return SyntaxVariant::asNode(_pFinalizationSection);
                case 5: return SyntaxVariant::asNode(_pEndOfModule);
                case 6: return SyntaxVariant::asToken(_pEOFToken);
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

pg_string DelphiUnitModuleSyntax::toString() const noexcept
{
    pg_stringstream str;
    str << L"DelphiUnitModuleSyntax(Position: " << _position << L", Kind: " << syntaxKindName(_syntaxKind) << L", Width: " << width() << L")";
    return str.str();
}

DelphiUnitModuleSyntax* DelphiUnitModuleSyntax::create(SyntaxFactory& syntaxFactory,
                                                       DelphiUnitHeadSyntax* head,
                                                       DelphiUnitInterfaceSectionSyntax* interfaceSection,
                                                       DelphiUnitImplementationSectionSyntax* implementationSection,
                                                       DelphiEndOfModuleExpressionSyntax* endOfModule,
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
    assert(endOfModule->syntaxKind() == SyntaxKind::EndOfModuleExpression);
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

    return static_cast<DelphiUnitModuleSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrUnitModuleSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
