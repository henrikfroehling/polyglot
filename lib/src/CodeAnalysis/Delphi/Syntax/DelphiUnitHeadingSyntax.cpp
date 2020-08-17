#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitHeadingSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitHeadingSyntax::DelphiUnitHeadingSyntax(SyntaxTokenPtr unitKeyword,
                                                 DelphiNameSyntaxPtr name) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitHeading},
      _ptrUnitKeyword{std::move(unitKeyword)},
      _ptrName{std::move(name)}
{}

} // end namespace polyglot::CodeAnalysis
