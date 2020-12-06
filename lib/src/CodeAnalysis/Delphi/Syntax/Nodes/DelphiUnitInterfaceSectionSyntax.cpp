#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInterfaceSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitInterfaceSectionSyntax::DelphiUnitInterfaceSectionSyntax(Ptr<SyntaxToken> interfaceKeyword) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitInterfaceSection},
      _ptrInterfaceKeyword{interfaceKeyword},
      _ptrUses{nullptr}
{}

} // end namespace polyglot::CodeAnalysis
