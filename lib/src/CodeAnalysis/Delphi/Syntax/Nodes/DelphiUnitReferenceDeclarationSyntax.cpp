#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitReferenceDeclarationSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitReferenceDeclarationSyntax::DelphiUnitReferenceDeclarationSyntax(DelphiNameSyntaxPtr unitName) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitReference},
      _ptrUnitName{std::move(unitName)},
      _ptrInKeyword{nullptr},
      _ptrSourceFile{nullptr},
      _ptrCommaToken{nullptr}
{}

} // end namespace polyglot::CodeAnalysis
