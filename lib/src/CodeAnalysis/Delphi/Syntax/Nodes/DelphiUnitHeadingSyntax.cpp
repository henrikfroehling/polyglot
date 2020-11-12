#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitHeadingSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitHeadingSyntax::DelphiUnitHeadingSyntax(SyntaxTokenPtr unitKeyword,
                                                 NameExpressionSyntaxPtr name,
                                                 SyntaxTokenPtr semiColonToken) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitHeading},
      _ptrUnitKeyword{std::move(unitKeyword)},
      _ptrName{std::move(name)},
      _ptrSemiColonToken{std::move(semiColonToken)}
{}

} // end namespace polyglot::CodeAnalysis
