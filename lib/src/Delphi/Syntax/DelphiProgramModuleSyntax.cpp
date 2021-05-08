#include "DelphiProgramModuleSyntax.hpp"
#include <cassert>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "DelphiProgramHeadSyntax.hpp"
#include "DelphiUsesClauseSyntax.hpp"

namespace polyglot::Delphi::Syntax
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
    _pHead->setChildNumber(0);
    adjustWidthAndFlags(_pUses);
    _pUses->setChildNumber(1);
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
    return dynamic_cast<DelphiProgramModuleSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrProgramModuleSyntax)));
}

DelphiProgramModuleSyntax* DelphiProgramModuleSyntax::create(SyntaxFactory& syntaxFactory) noexcept
{
    auto ptrProgramModuleSyntax = std::make_unique<DelphiProgramModuleSyntax>(nullptr, nullptr, nullptr);
    return dynamic_cast<DelphiProgramModuleSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrProgramModuleSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
