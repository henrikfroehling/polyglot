#include "CodeAnalysis/Delphi/Syntax/DelphiUsesClauseSyntax.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxList.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

DelphiUsesClauseSyntax::DelphiUsesClauseSyntax(LanguageSyntaxToken* usesKeyword,
                                               LanguageSyntaxList* unitReferences,
                                               LanguageSyntaxToken* semiColonToken) noexcept
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

LanguageSyntaxNode* DelphiUsesClauseSyntax::child(pg_size index) const
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
                                                       LanguageSyntaxToken* usesKeyword,
                                                       LanguageSyntaxList* unitReferences,
                                                       LanguageSyntaxToken* semiColonToken) noexcept
{
    assert(usesKeyword != nullptr);
    assert(usesKeyword->syntaxKind() == SyntaxKind::UsesKeyword);
    assert(unitReferences != nullptr);
    assert(unitReferences->childCount() > 0);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrUsesClauseSyntax = std::make_unique<DelphiUsesClauseSyntax>(usesKeyword, unitReferences, semiColonToken);
    return static_cast<DelphiUsesClauseSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrUsesClauseSyntax)));
}

} // end namespace polyglot::CodeAnalysis
