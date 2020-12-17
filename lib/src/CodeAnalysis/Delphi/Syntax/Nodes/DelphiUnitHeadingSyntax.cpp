#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitHeadingSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitHeadingSyntax::DelphiUnitHeadingSyntax(SyntaxToken* unitKeyword,
                                                 NameExpressionSyntax* name,
                                                 SyntaxToken* semiColonToken) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitHeading},
      _pUnitKeyword{unitKeyword},
      _pName{name},
      _pSemiColonToken{semiColonToken}
{}

} // end namespace polyglot::CodeAnalysis
