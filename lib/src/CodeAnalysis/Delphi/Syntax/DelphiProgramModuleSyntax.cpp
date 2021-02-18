#include "CodeAnalysis/Delphi/Syntax/DelphiProgramModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiProgramHeadSyntax.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiUsesClauseSyntax.hpp"
#include <cassert>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

DelphiProgramModuleSyntax::DelphiProgramModuleSyntax(DelphiProgramHeadSyntax* head,
                                                     DelphiUsesClauseSyntax* uses,
                                                     ISyntaxToken* EOFToken) noexcept
    : DelphiCompilationUnitSyntax{SyntaxKind::ProgramModule, EOFToken},
      _pHead{head},
      _pUses{uses}
{
    _position = _pHead->position();
    adjustWidthAndFlags(_pHead);
    adjustWidthAndFlags(_pUses);
}

ISyntaxNode* DelphiProgramModuleSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pHead;
        case 1: return _pUses;
    }

    throw std::out_of_range{"index out of range"};
}

DelphiProgramModuleSyntax* DelphiProgramModuleSyntax::create(SyntaxFactory& syntaxFactory,
                                                             DelphiProgramHeadSyntax* head,
                                                             DelphiUsesClauseSyntax* uses,
                                                             ISyntaxToken* EOFToken) noexcept
{
    assert(head != nullptr);
    assert(head->syntaxKind() == SyntaxKind::ProgramHead);
    assert(uses != nullptr);
    assert(uses->syntaxKind() == SyntaxKind::UsesClause);
    assert(EOFToken != nullptr);
    assert(EOFToken->syntaxKind() == SyntaxKind::EndOfFileToken);

    auto ptrProgramModuleSyntax = std::make_unique<DelphiProgramModuleSyntax>(head, uses, EOFToken);
    return static_cast<DelphiProgramModuleSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrProgramModuleSyntax)));
}

DelphiProgramModuleSyntax* DelphiProgramModuleSyntax::create(SyntaxFactory& syntaxFactory) noexcept
{
    auto ptrProgramModuleSyntax = std::make_unique<DelphiProgramModuleSyntax>(nullptr, nullptr, nullptr);
    return static_cast<DelphiProgramModuleSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrProgramModuleSyntax)));
}

} // end namespace polyglot::CodeAnalysis
