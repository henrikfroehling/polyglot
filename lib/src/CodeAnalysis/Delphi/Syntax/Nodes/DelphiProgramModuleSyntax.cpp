#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiProgramModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiProgramHeadingSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

DelphiProgramModuleSyntax::DelphiProgramModuleSyntax(DelphiProgramHeadingSyntax* heading,
                                                     DelphiUsesClauseSyntax* uses,
                                                     LanguageSyntaxToken* EOFToken) noexcept
    : DelphiCompilationUnitSyntax{SyntaxKind::ProgramModule, EOFToken},
      _pHeading{heading},
      _pUses{uses}
{
    adjustWidthAndFlags(_pHeading);
    adjustWidthAndFlags(_pUses);
}

DelphiProgramModuleSyntax* DelphiProgramModuleSyntax::create(SyntaxFactory& syntaxFactory,
                                                             DelphiProgramHeadingSyntax* heading,
                                                             DelphiUsesClauseSyntax* uses,
                                                             LanguageSyntaxToken* EOFToken) noexcept
{
    assert(heading != nullptr);
    assert(heading->syntaxKind() == SyntaxKind::ProgramHeading);
    assert(uses != nullptr);
    assert(uses->syntaxKind() == SyntaxKind::UsesClause);
    assert(EOFToken != nullptr);
    assert(EOFToken->syntaxKind() == SyntaxKind::EndOfFileToken);

    auto ptrProgramModuleSyntax = std::make_unique<DelphiProgramModuleSyntax>(heading, uses, EOFToken);
    return static_cast<DelphiProgramModuleSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrProgramModuleSyntax)));
}

DelphiProgramModuleSyntax* DelphiProgramModuleSyntax::create(SyntaxFactory& syntaxFactory) noexcept
{
    auto ptrProgramModuleSyntax = std::make_unique<DelphiProgramModuleSyntax>(nullptr, nullptr, nullptr);
    return static_cast<DelphiProgramModuleSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrProgramModuleSyntax)));
}

} // end namespace polyglot::CodeAnalysis
