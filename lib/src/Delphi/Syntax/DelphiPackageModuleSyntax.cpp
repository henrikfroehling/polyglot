#include "Delphi/Syntax/DelphiPackageModuleSyntax.hpp"
#include <cassert>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/DelphiPackageContainsClauseSyntax.hpp"
#include "Delphi/Syntax/DelphiPackageHeadSyntax.hpp"
#include "Delphi/Syntax/DelphiPackageRequiresClauseSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::ISyntaxToken;
using Core::Syntax::SyntaxFactory;
using Core::Syntax::SyntaxKind;
using Core::Syntax::SyntaxVariant;

DelphiPackageModuleSyntax::DelphiPackageModuleSyntax(DelphiPackageHeadSyntax* head,
                                                     DelphiPackageRequiresClauseSyntax* requiresClause,
                                                     DelphiPackageContainsClauseSyntax* containsClause,
                                                     ISyntaxToken* EOFToken) noexcept
    : DelphiCompilationUnitSyntax{SyntaxKind::PackageModule, EOFToken},
      _pHead{head},
      _pRequiresClause{requiresClause},
      _pContainsClause{containsClause}
{
    _position = _pHead->position();
    adjustWidthAndFlags(_pHead);
    adjustWidthAndFlags(_pRequiresClause);
    adjustWidthAndFlags(_pContainsClause);
}

SyntaxVariant DelphiPackageModuleSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asNode(_pHead);
        case 1: return SyntaxVariant::asNode(_pRequiresClause);
        case 2: return SyntaxVariant::asNode(_pContainsClause);
        case 3: return SyntaxVariant::asToken(_pEOFToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiPackageModuleSyntax* DelphiPackageModuleSyntax::create(SyntaxFactory& syntaxFactory,
                                                             DelphiPackageHeadSyntax* head,
                                                             DelphiPackageRequiresClauseSyntax* requiresClause,
                                                             DelphiPackageContainsClauseSyntax* containsClause,
                                                             ISyntaxToken* EOFToken) noexcept
{
    assert(head != nullptr);
    assert(head->syntaxKind() == SyntaxKind::PackageHead);
    assert(requiresClause != nullptr);
    assert(requiresClause->syntaxKind() == SyntaxKind::PackageRequiresClause);
    assert(containsClause != nullptr);
    assert(containsClause->syntaxKind() == SyntaxKind::PackageContainsClause);
    assert(EOFToken != nullptr);
    assert(EOFToken->syntaxKind() == SyntaxKind::EndOfFileToken);

    auto ptrPackageModuleSyntax = std::make_unique<DelphiPackageModuleSyntax>(head, requiresClause, containsClause, EOFToken);
    return static_cast<DelphiPackageModuleSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrPackageModuleSyntax)));
}

DelphiPackageModuleSyntax* DelphiPackageModuleSyntax::create(SyntaxFactory& syntaxFactory) noexcept
{
    auto ptrPackageModuleSyntax = std::make_unique<DelphiPackageModuleSyntax>(nullptr, nullptr, nullptr, nullptr);
    return static_cast<DelphiPackageModuleSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrPackageModuleSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
