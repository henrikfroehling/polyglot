#include "CodeAnalysis/Delphi/Syntax/DelphiUsesClauseSyntax.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxList.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include <cassert>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

DelphiUsesClauseSyntax::DelphiUsesClauseSyntax(ISyntaxToken* usesKeyword,
                                               ISyntaxList* unitReferences,
                                               ISyntaxToken* semiColonToken) noexcept
    : DelphiSyntaxList{SyntaxKind::UsesClause},
      _pUsesKeyword{usesKeyword},
      _pUnitReferences{unitReferences},
      _pSemiColonToken{semiColonToken}
{
    _position = _pUsesKeyword->position();
    adjustWidthAndFlags(_pUsesKeyword);
    adjustWidthAndFlags(_pUnitReferences);
    adjustWidthAndFlags(_pSemiColonToken);
}

ISyntaxNode* DelphiUsesClauseSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pUsesKeyword;
        case 1: return _pUnitReferences;
        case 2: return _pSemiColonToken;
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
    assert(unitReferences->childCount() > 0);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrUsesClauseSyntax = std::make_unique<DelphiUsesClauseSyntax>(usesKeyword, unitReferences, semiColonToken);
    return dynamic_cast<DelphiUsesClauseSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrUsesClauseSyntax)));
}

} // end namespace polyglot::CodeAnalysis
