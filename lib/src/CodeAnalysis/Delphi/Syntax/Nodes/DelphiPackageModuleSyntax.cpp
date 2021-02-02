#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageHeadingSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageRequiresClauseSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageContainsClauseSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

DelphiPackageModuleSyntax::DelphiPackageModuleSyntax(DelphiPackageHeadingSyntax* heading,
                                                     DelphiPackageRequiresClauseSyntax* requiresClause,
                                                     DelphiPackageContainsClauseSyntax* containsClause,
                                                     LanguageSyntaxToken* EOFToken) noexcept
    : DelphiCompilationUnitSyntax{SyntaxKind::PackageModule, EOFToken},
      _pHeading{heading},
      _pRequiresClause{requiresClause},
      _pContainsClause{containsClause}
{
    adjustWidthAndFlags(_pHeading);
    adjustWidthAndFlags(_pRequiresClause);
    adjustWidthAndFlags(_pContainsClause);
}

DelphiPackageModuleSyntax* DelphiPackageModuleSyntax::create(DelphiPackageHeadingSyntax* heading,
                                                             DelphiPackageRequiresClauseSyntax* requiresClause,
                                                             DelphiPackageContainsClauseSyntax* containsClause,
                                                             LanguageSyntaxToken* EOFToken) noexcept
{
    assert(heading != nullptr);
    assert(heading->syntaxKind() == SyntaxKind::PackageHeading);
    assert(requiresClause != nullptr);
    assert(requiresClause->syntaxKind() == SyntaxKind::PackageRequiresClause);
    assert(containsClause != nullptr);
    assert(containsClause->syntaxKind() == SyntaxKind::PackageContainsClause);
    assert(EOFToken != nullptr);
    assert(EOFToken->syntaxKind() == SyntaxKind::EndOfFileToken);

    auto ptrPackageModuleSyntax = std::make_unique<DelphiPackageModuleSyntax>(heading, requiresClause, containsClause, EOFToken);
    return static_cast<DelphiPackageModuleSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrPackageModuleSyntax)));
}

DelphiPackageModuleSyntax* DelphiPackageModuleSyntax::create() noexcept
{
    auto ptrPackageModuleSyntax = std::make_unique<DelphiPackageModuleSyntax>(nullptr, nullptr, nullptr, nullptr);
    return static_cast<DelphiPackageModuleSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrPackageModuleSyntax)));
}

} // end namespace polyglot::CodeAnalysis
