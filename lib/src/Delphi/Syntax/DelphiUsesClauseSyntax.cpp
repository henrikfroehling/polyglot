#include "Delphi/Syntax/DelphiUsesClauseSyntax.hpp"
#include <cassert>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxList.hpp"
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::ISyntaxList;
using Core::Syntax::ISyntaxToken;
using Core::Syntax::SyntaxFactory;
using Core::Syntax::SyntaxKind;
using Core::Syntax::SyntaxVariant;

DelphiUsesClauseSyntax::DelphiUsesClauseSyntax(ISyntaxToken* usesKeyword,
                                               ISyntaxList* unitReferences,
                                               ISyntaxToken* semiColonToken) noexcept
    : DelphiSyntaxNode{SyntaxKind::UsesClause},
      _pUsesKeyword{usesKeyword},
      _pUnitReferences{unitReferences},
      _pSemiColonToken{semiColonToken}
{
    _position = _pUsesKeyword->position();
    adjustWidthAndFlags(_pUsesKeyword);
    adjustWidthAndFlags(_pUnitReferences);
    adjustWidthAndFlags(_pSemiColonToken);
}

SyntaxVariant DelphiUsesClauseSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pUsesKeyword);
        case 1: return SyntaxVariant::asList(_pUnitReferences);
        case 2: return SyntaxVariant::asToken(_pSemiColonToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiUsesClauseSyntax* DelphiUsesClauseSyntax::create(SyntaxFactory& syntaxFactory,
                                                       ISyntaxToken* usesKeyword,
                                                       ISyntaxList* unitReferences,
                                                       ISyntaxToken* semiColonToken) noexcept
{
    assert(usesKeyword != nullptr);
    assert(usesKeyword->syntaxKind() == SyntaxKind::UsesKeyword);
    assert(unitReferences != nullptr);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrUsesClauseSyntax = std::make_unique<DelphiUsesClauseSyntax>(usesKeyword, unitReferences, semiColonToken);
    return static_cast<DelphiUsesClauseSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrUsesClauseSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
