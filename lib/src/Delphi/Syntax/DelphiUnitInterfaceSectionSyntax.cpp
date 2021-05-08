#include "DelphiUnitInterfaceSectionSyntax.hpp"
#include <cassert>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "DelphiUsesClauseSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiUnitInterfaceSectionSyntax::DelphiUnitInterfaceSectionSyntax(ISyntaxToken* interfaceKeyword,
                                                                   DelphiUsesClauseSyntax* uses) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitInterfaceSection},
      _pInterfaceKeyword{interfaceKeyword},
      _pUses{uses}
{
    _position = _pInterfaceKeyword->position();
    adjustWidthAndFlags(_pInterfaceKeyword);
    _pInterfaceKeyword->setChildNumber(0);

    if (_pUses != nullptr)
    {
        adjustWidthAndFlags(_pUses);
        _pUses->setChildNumber(1);
    }
}

ISyntaxNode* DelphiUnitInterfaceSectionSyntax::child(pg_size index) const
{
    switch (childCount())
    {
        case 1:
        {
            if (index == 0)
                return _pInterfaceKeyword;
        }
        case 2:
        {
            switch (index)
            {
                case 0: return _pInterfaceKeyword;
                case 1: return _pUses;
            }
        }
    }

    throw std::out_of_range{"index out of range"};
}

DelphiUnitInterfaceSectionSyntax* DelphiUnitInterfaceSectionSyntax::create(SyntaxFactory& syntaxFactory,
                                                                           ISyntaxToken* interfaceKeyword,
                                                                           DelphiUsesClauseSyntax* uses) noexcept
{
    assert(interfaceKeyword != nullptr);
    assert(interfaceKeyword->syntaxKind() == SyntaxKind::InterfaceKeyword);

    if (uses != nullptr)
        assert(uses->syntaxKind() == SyntaxKind::UsesClause);

    auto ptrUnitInterfaceSectionSyntax = std::make_unique<DelphiUnitInterfaceSectionSyntax>(interfaceKeyword, uses);
    return dynamic_cast<DelphiUnitInterfaceSectionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrUnitInterfaceSectionSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
