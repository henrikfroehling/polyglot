#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitInterfaceSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitInterfaceSectionSyntax::DelphiUnitInterfaceSectionSyntax(SyntaxTokenPtr interfaceKeyword) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitInterfaceSection},
      _ptrInterfaceKeyword{std::move(interfaceKeyword)},
      _ptrUses{nullptr}
{}

} // end namespace polyglot::CodeAnalysis
