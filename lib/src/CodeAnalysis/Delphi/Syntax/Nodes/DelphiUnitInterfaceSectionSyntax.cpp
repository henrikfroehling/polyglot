#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInterfaceSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitInterfaceSectionSyntax::DelphiUnitInterfaceSectionSyntax(LanguageSyntaxToken* interfaceKeyword) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitInterfaceSection},
      _pInterfaceKeyword{interfaceKeyword},
      _pUses{nullptr}
{}

} // end namespace polyglot::CodeAnalysis
