#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitReferenceDeclarationSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitReferenceDeclarationSyntax::DelphiUnitReferenceDeclarationSyntax(NameExpressionSyntax* unitName) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitReference},
      _pUnitName{unitName},
      _pInKeyword{nullptr},
      _pSourceFile{nullptr},
      _pCommaToken{nullptr}
{}

} // end namespace polyglot::CodeAnalysis
