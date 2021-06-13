#include "Delphi/Syntax/DelphiCaseItemSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiCaseItemSyntax::DelphiCaseItemSyntax(DelphiCaseLabelListSyntax* caseLabels,
                                           Core::Syntax::ISyntaxToken* colonToken,
                                           DelphiStatementSyntax* statement) noexcept
    : DelphiSyntaxNode{SyntaxKind::CaseItem},
      _pCaseLabels{caseLabels},
      _pColonToken{colonToken},
      _pStatement{statement}
{}

DelphiCaseItemSyntax* DelphiCaseItemSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                   DelphiCaseLabelListSyntax* caseLabels,
                                                   Core::Syntax::ISyntaxToken* colonToken,
                                                   DelphiStatementSyntax* statement) noexcept
{
    assert(caseLabels != nullptr);
    assert(colonToken != nullptr);
    assert(colonToken->syntaxKind() == SyntaxKind::ColonToken);
    assert(statement != nullptr);

    auto ptrCaseItemSyntax = std::make_unique<DelphiCaseItemSyntax>(caseLabels, colonToken, statement);
    return static_cast<DelphiCaseItemSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrCaseItemSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
