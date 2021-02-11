#include "CodeAnalysis/Delphi/Syntax/DelphiUnitImplementationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiUsesClauseSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

DelphiUnitImplementationSectionSyntax::DelphiUnitImplementationSectionSyntax(LanguageSyntaxToken* implementationKeyword,
                                                                             DelphiUsesClauseSyntax* uses) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitImplementationSection},
      _pImplementationKeyword{implementationKeyword},
      _pUses{uses}
{
    _position = _pImplementationKeyword->position();
    adjustWidthAndFlags(_pImplementationKeyword);

    if (_pUses != nullptr)
        adjustWidthAndFlags(_pUses);
}

DelphiUnitImplementationSectionSyntax* DelphiUnitImplementationSectionSyntax::create(SyntaxFactory& syntaxFactory,
                                                                                     LanguageSyntaxToken* implementationKeyword,
                                                                                     DelphiUsesClauseSyntax* uses) noexcept
{
    assert(implementationKeyword != nullptr);
    assert(implementationKeyword->syntaxKind() == SyntaxKind::ImplementationKeyword);

    if (uses != nullptr)
        assert(uses->syntaxKind() == SyntaxKind::UsesClause);

    auto ptrUnitImplementationSectionSyntax = std::make_unique<DelphiUnitImplementationSectionSyntax>(implementationKeyword, uses);
    return static_cast<DelphiUnitImplementationSectionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrUnitImplementationSectionSyntax)));
}

} // end namespace polyglot::CodeAnalysis
