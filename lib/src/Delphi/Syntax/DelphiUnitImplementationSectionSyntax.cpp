#include "DelphiUnitImplementationSectionSyntax.hpp"
#include <cassert>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "DelphiUsesClauseSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::ISyntaxToken;
using Core::Syntax::SyntaxFactory;
using Core::Syntax::SyntaxKind;
using Core::Syntax::SyntaxVariant;

DelphiUnitImplementationSectionSyntax::DelphiUnitImplementationSectionSyntax(ISyntaxToken* implementationKeyword,
                                                                             DelphiUsesClauseSyntax* uses) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitImplementationSection},
      _pImplementationKeyword{implementationKeyword},
      _pUses{uses}
{
    _position = _pImplementationKeyword->position();
    adjustWidthAndFlags(_pImplementationKeyword);

    if (_pUses != nullptr)
        adjustWidthAndFlags(dynamic_cast<SyntaxNode*>(_pUses));
}

SyntaxVariant DelphiUnitImplementationSectionSyntax::child(pg_size index) const
{
    switch (childCount())
    {
        case 1:
        {
            if (index == 0)
                return SyntaxVariant::asToken(_pImplementationKeyword);

            break;
        }
        case 2:
        {
            switch (index)
            {
                case 0: return SyntaxVariant::asToken(_pImplementationKeyword);
                case 1: return SyntaxVariant::asNode(dynamic_cast<SyntaxNode*>(_pUses));
            }
        }
    }

    throw std::out_of_range{"index out of range"};
}

DelphiUnitImplementationSectionSyntax* DelphiUnitImplementationSectionSyntax::create(SyntaxFactory& syntaxFactory,
                                                                                     ISyntaxToken* implementationKeyword,
                                                                                     DelphiUsesClauseSyntax* uses) noexcept
{
    assert(implementationKeyword != nullptr);
    assert(implementationKeyword->syntaxKind() == SyntaxKind::ImplementationKeyword);

    if (uses != nullptr)
        assert(dynamic_cast<SyntaxNode*>(uses)->syntaxKind() == SyntaxKind::UsesClause);

    auto ptrUnitImplementationSectionSyntax = std::make_unique<DelphiUnitImplementationSectionSyntax>(implementationKeyword, uses);
    return dynamic_cast<DelphiUnitImplementationSectionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrUnitImplementationSectionSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
