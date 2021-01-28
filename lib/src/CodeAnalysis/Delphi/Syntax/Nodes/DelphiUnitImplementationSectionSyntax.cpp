#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitImplementationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitImplementationSectionSyntax::DelphiUnitImplementationSectionSyntax(LanguageSyntaxToken* implementationKeyword) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitImplementationSection},
      _pImplementationKeyword{implementationKeyword},
      _pUses{nullptr}
{
    adjustWidthAndFlags(_pImplementationKeyword);
}

void DelphiUnitImplementationSectionSyntax::setUses(DelphiUsesClauseSyntax* uses) noexcept
{
    _pUses = uses;
    adjustWidthAndFlags(_pUses);
}

} // end namespace polyglot::CodeAnalysis
