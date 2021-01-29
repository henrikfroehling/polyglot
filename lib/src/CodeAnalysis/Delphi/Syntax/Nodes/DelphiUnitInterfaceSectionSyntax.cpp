#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInterfaceSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

DelphiUnitInterfaceSectionSyntax::DelphiUnitInterfaceSectionSyntax(LanguageSyntaxToken* interfaceKeyword,
                                                                   DelphiUsesClauseSyntax* uses) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitInterfaceSection},
      _pInterfaceKeyword{interfaceKeyword},
      _pUses{uses}
{
    adjustWidthAndFlags(_pInterfaceKeyword);

    if (_pUses != nullptr)
        adjustWidthAndFlags(_pUses);
}

DelphiUnitInterfaceSectionSyntax* DelphiUnitInterfaceSectionSyntax::create(LanguageSyntaxToken* interfaceKeyword,
                                                                           DelphiUsesClauseSyntax* uses) noexcept
{
    assert(interfaceKeyword != nullptr);
    assert(interfaceKeyword->syntaxKind() == SyntaxKind::InterfaceKeyword);

    if (uses != nullptr)
        assert(uses->syntaxKind() == SyntaxKind::UsesClause);

    auto ptrUnitInterfaceSectionSyntax = std::make_unique<DelphiUnitInterfaceSectionSyntax>(interfaceKeyword, uses);
    return static_cast<DelphiUnitInterfaceSectionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrUnitInterfaceSectionSyntax)));
}

} // end namespace polyglot::CodeAnalysis
