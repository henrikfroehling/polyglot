#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitHeadingSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitHeadingSyntax::DelphiUnitHeadingSyntax(LanguageSyntaxToken* unitKeyword,
                                                 NameExpressionSyntax* name,
                                                 LanguageSyntaxToken* semiColonToken) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitHeading},
      _pUnitKeyword{unitKeyword},
      _pName{name},
      _pSemiColonToken{semiColonToken}
{}

} // end namespace polyglot::CodeAnalysis
