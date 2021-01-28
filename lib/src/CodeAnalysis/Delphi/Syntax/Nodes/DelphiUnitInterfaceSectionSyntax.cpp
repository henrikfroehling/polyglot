#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInterfaceSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitInterfaceSectionSyntax::DelphiUnitInterfaceSectionSyntax(LanguageSyntaxToken* interfaceKeyword) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitInterfaceSection},
      _pInterfaceKeyword{interfaceKeyword},
      _pUses{nullptr}
{
    adjustWidthAndFlags(_pInterfaceKeyword);
}

void DelphiUnitInterfaceSectionSyntax::setUses(DelphiUsesClauseSyntax* uses) noexcept
{
    _pUses = uses;
    adjustWidthAndFlags(_pUses);
}

} // end namespace polyglot::CodeAnalysis
