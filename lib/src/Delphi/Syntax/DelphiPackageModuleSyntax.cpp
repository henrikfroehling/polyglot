#include "DelphiPackageModuleSyntax.hpp"
#include <cassert>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "DelphiPackageContainsClauseSyntax.hpp"
#include "DelphiPackageHeadSyntax.hpp"
#include "DelphiPackageRequiresClauseSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

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
    _pHead->setChildNumber(0);
    adjustWidthAndFlags(_pRequiresClause);
    _pRequiresClause->setChildNumber(1);
    adjustWidthAndFlags(_pContainsClause);
    _pContainsClause->setChildNumber(2);
}

ISyntaxNode* DelphiPackageModuleSyntax::child(pg_size index) const
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
    return dynamic_cast<DelphiPackageModuleSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrPackageModuleSyntax)));
}

DelphiPackageModuleSyntax* DelphiPackageModuleSyntax::create(SyntaxFactory& syntaxFactory) noexcept
{
    auto ptrPackageModuleSyntax = std::make_unique<DelphiPackageModuleSyntax>(nullptr, nullptr, nullptr, nullptr);
    return dynamic_cast<DelphiPackageModuleSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrPackageModuleSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
