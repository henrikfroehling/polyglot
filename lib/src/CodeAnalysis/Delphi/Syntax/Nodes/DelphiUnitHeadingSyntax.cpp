#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitHeadingSyntax.hpp"
#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxPool.hpp"
#include "CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

DelphiUnitHeadingSyntax::DelphiUnitHeadingSyntax(LanguageSyntaxToken* unitKeyword,
                                                 NameExpressionSyntax* name,
                                                 LanguageSyntaxToken* semiColonToken) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitHeading},
      _pUnitKeyword{unitKeyword},
      _pName{name},
      _pSemiColonToken{semiColonToken}
{
    adjustWidthAndFlags(_pUnitKeyword);
    adjustWidthAndFlags(_pName);
    adjustWidthAndFlags(_pSemiColonToken);
}

DelphiUnitHeadingSyntax* DelphiUnitHeadingSyntax::create(LanguageSyntaxToken* unitKeyword,
                                                         NameExpressionSyntax* name,
                                                         LanguageSyntaxToken* semiColonToken) noexcept
{
    assert(unitKeyword != nullptr);
    assert(unitKeyword->syntaxKind() == SyntaxKind::UnitKeyword);
    assert(name != nullptr);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrUnitHeadingSyntax = std::make_unique<DelphiUnitHeadingSyntax>(unitKeyword, name, semiColonToken);
    return static_cast<DelphiUnitHeadingSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrUnitHeadingSyntax)));
}

} // end namespace polyglot::CodeAnalysis
