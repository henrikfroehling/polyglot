#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInterfaceSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitInterfaceSectionSyntax::DelphiUnitInterfaceSectionSyntax(SyntaxToken* interfaceKeyword) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitInterfaceSection},
      _pInterfaceKeyword{interfaceKeyword},
      _pUses{nullptr}
{}

} // end namespace polyglot::CodeAnalysis
