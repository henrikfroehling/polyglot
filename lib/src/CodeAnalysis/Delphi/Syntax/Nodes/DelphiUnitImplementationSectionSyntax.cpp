#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitImplementationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

DelphiUnitImplementationSectionSyntax::DelphiUnitImplementationSectionSyntax(LanguageSyntaxToken* implementationKeyword,
                                                                             DelphiUsesClauseSyntax* uses) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitImplementationSection},
      _pImplementationKeyword{implementationKeyword},
      _pUses{uses}
{
    adjustWidthAndFlags(_pImplementationKeyword);

    if (_pUses != nullptr)
        adjustWidthAndFlags(_pUses);
}

DelphiUnitImplementationSectionSyntax* DelphiUnitImplementationSectionSyntax::create(LanguageSyntaxToken* implementationKeyword,
                                                                                     DelphiUsesClauseSyntax* uses) noexcept
{
    assert(implementationKeyword != nullptr);
    assert(implementationKeyword->syntaxKind() == SyntaxKind::ImplementationKeyword);

    if (uses != nullptr)
        assert(uses->syntaxKind() == SyntaxKind::UsesClause);

    auto ptrUnitImplementationSectionSyntax = std::make_unique<DelphiUnitImplementationSectionSyntax>(implementationKeyword, uses);
    return static_cast<DelphiUnitImplementationSectionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrUnitImplementationSectionSyntax)));
}

} // end namespace polyglot::CodeAnalysis
