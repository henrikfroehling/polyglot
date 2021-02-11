#include "CodeAnalysis/Delphi/Syntax/DelphiUnitHeadSyntax.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

DelphiUnitHeadSyntax::DelphiUnitHeadSyntax(LanguageSyntaxToken* unitKeyword,
                                           NameExpressionSyntax* name,
                                           LanguageSyntaxToken* semiColonToken) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitHead},
      _pUnitKeyword{unitKeyword},
      _pName{name},
      _pSemiColonToken{semiColonToken}
{
    _position = _pUnitKeyword->position();
    adjustWidthAndFlags(_pUnitKeyword);
    adjustWidthAndFlags(_pName);
    adjustWidthAndFlags(_pSemiColonToken);
}

DelphiUnitHeadSyntax* DelphiUnitHeadSyntax::create(SyntaxFactory& syntaxFactory,
                                                   LanguageSyntaxToken* unitKeyword,
                                                   NameExpressionSyntax* name,
                                                   LanguageSyntaxToken* semiColonToken) noexcept
{
    assert(unitKeyword != nullptr);
    assert(unitKeyword->syntaxKind() == SyntaxKind::UnitKeyword);
    assert(name != nullptr);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrUnitHeadingSyntax = std::make_unique<DelphiUnitHeadSyntax>(unitKeyword, name, semiColonToken);
    return static_cast<DelphiUnitHeadSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrUnitHeadingSyntax)));
}

} // end namespace polyglot::CodeAnalysis
