#include "Delphi/Syntax/DelphiUnitInterfaceSectionSyntax.hpp"
#include <cassert>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Core/Syntax/SyntaxList.hpp"
#include "Delphi/Syntax/DelphiUsesClauseSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::ISyntaxToken;
using Core::Syntax::SyntaxFactory;
using Core::Syntax::SyntaxKind;
using Core::Syntax::SyntaxVariant;

DelphiUnitInterfaceSectionSyntax::DelphiUnitInterfaceSectionSyntax(ISyntaxToken* interfaceKeyword,
                                                                   DelphiUsesClauseSyntax* uses) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitInterfaceSection},
      _pInterfaceKeyword{interfaceKeyword},
      _pUses{uses}
{
    _position = _pInterfaceKeyword->position();
    adjustWidthAndFlags(_pInterfaceKeyword);

    if (_pUses != nullptr)
        adjustWidthAndFlags(static_cast<SyntaxNode*>(_pUses));
}

SyntaxVariant DelphiUnitInterfaceSectionSyntax::child(pg_size index) const
{
    switch (childCount())
    {
        case 1:
        {
            if (index == 0)
                return SyntaxVariant::asToken(_pInterfaceKeyword);

            break;
        }
        case 2:
        {
            switch (index)
            {
                case 0: return SyntaxVariant::asToken(_pInterfaceKeyword);
                case 1: return SyntaxVariant::asNode(static_cast<SyntaxNode*>(_pUses));
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
        assert(static_cast<Core::Syntax::SyntaxList*>(uses)->syntaxKind() == SyntaxKind::UsesClause);

    auto ptrUnitInterfaceSectionSyntax = std::make_unique<DelphiUnitInterfaceSectionSyntax>(interfaceKeyword, uses);
    return static_cast<DelphiUnitInterfaceSectionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrUnitInterfaceSectionSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
