#include "CodeAnalysis/Delphi/Syntax/DelphiUnitInterfaceSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiUsesClauseSyntax.hpp"
#include <cassert>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

DelphiUnitInterfaceSectionSyntax::DelphiUnitInterfaceSectionSyntax(ISyntaxToken* interfaceKeyword,
                                                                   DelphiUsesClauseSyntax* uses) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitInterfaceSection},
      _pInterfaceKeyword{interfaceKeyword},
      _pUses{uses}
{
    _position = _pInterfaceKeyword->position();
    adjustWidthAndFlags(_pInterfaceKeyword);

    if (_pUses != nullptr)
        adjustWidthAndFlags(_pUses);
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

} // end namespace polyglot::CodeAnalysis
