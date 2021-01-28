#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitHeadingSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Core/Syntax/Expressions/NameExpressionSyntax.hpp"

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

} // end namespace polyglot::CodeAnalysis
