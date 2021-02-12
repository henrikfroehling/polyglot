#include "CodeAnalysis/Delphi/Syntax/DelphiPackageModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiPackageHeadSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiPackageRequiresClauseSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiPackageContainsClauseSyntax.hpp"
#include <cassert>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

DelphiPackageModuleSyntax::DelphiPackageModuleSyntax(DelphiPackageHeadSyntax* head,
                                                     DelphiPackageRequiresClauseSyntax* requiresClause,
                                                     DelphiPackageContainsClauseSyntax* containsClause,
                                                     LanguageSyntaxToken* EOFToken) noexcept
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

LanguageSyntaxNode* DelphiPackageModuleSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pHead;
        case 1: return _pRequiresClause;
        case 2: return _pContainsClause;
    }

    throw std::out_of_range{"index out of range"};
}

DelphiPackageModuleSyntax* DelphiPackageModuleSyntax::create(SyntaxFactory& syntaxFactory,
                                                             DelphiPackageHeadSyntax* head,
                                                             DelphiPackageRequiresClauseSyntax* requiresClause,
                                                             DelphiPackageContainsClauseSyntax* containsClause,
                                                             LanguageSyntaxToken* EOFToken) noexcept
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

} // end namespace polyglot::CodeAnalysis
