#include "Delphi/Syntax/DelphiProgramModuleSyntax.hpp"
#include <cassert>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/DelphiProgramHeadSyntax.hpp"
#include "Delphi/Syntax/DelphiUsesClauseSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::ISyntaxToken;
using Core::Syntax::SyntaxFactory;
using Core::Syntax::SyntaxKind;
using Core::Syntax::SyntaxVariant;

DelphiProgramModuleSyntax::DelphiProgramModuleSyntax(DelphiProgramHeadSyntax* head,
                                                     DelphiUsesClauseSyntax* uses,
                                                     ISyntaxToken* EOFToken) noexcept
    : DelphiCompilationUnitSyntax{SyntaxKind::ProgramModule, EOFToken},
      _pHead{head},
      _pUses{uses}
{
    _position = _pHead->position();
    adjustWidthAndFlags(_pHead);
    adjustWidthAndFlags(static_cast<SyntaxNode*>(_pUses));
}

SyntaxVariant DelphiProgramModuleSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asNode(_pHead);
        case 1: return SyntaxVariant::asNode(_pUses);
        case 2: return SyntaxVariant::asToken(_pEOFToken);
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

} // end namespace polyglot::Delphi::Syntax
