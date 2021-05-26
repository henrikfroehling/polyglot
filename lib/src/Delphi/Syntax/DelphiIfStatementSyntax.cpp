#include "Delphi/Syntax/DelphiIfStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/DelphiStatementListSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiIfStatementSyntax::DelphiIfStatementSyntax(Core::Syntax::ISyntaxToken* ifKeyword,
                                                 DelphiExpressionSyntax* conditionExpression,
                                                 Core::Syntax::ISyntaxToken* thenKeyword,
                                                 DelphiStatementListSyntax* statementList) noexcept
    : DelphiStatementSyntax{SyntaxKind::IfStatement},
      _pIfKeyword{ifKeyword},
      _pConditionExpression{conditionExpression},
      _pThenKeyword{thenKeyword},
      _pStatementList{statementList}
{}

DelphiIfStatementSyntax* DelphiIfStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                         Core::Syntax::ISyntaxToken* ifKeyword,
                                                         DelphiExpressionSyntax* conditionExpression,
                                                         Core::Syntax::ISyntaxToken* thenKeyword,
                                                         DelphiStatementListSyntax* statementList) noexcept
{
    assert(ifKeyword != nullptr);
    assert(ifKeyword->syntaxKind() == SyntaxKind::IfKeyword);
    assert(conditionExpression != nullptr);
    assert(thenKeyword != nullptr);
    assert(thenKeyword->syntaxKind() == SyntaxKind::ThenKeyword);
    assert(statementList != nullptr);
    assert(statementList->syntaxKind() == SyntaxKind::StatementList);

    auto ptrIfStatementSyntax = std::make_unique<DelphiIfStatementSyntax>(ifKeyword, conditionExpression, thenKeyword, statementList);
    return static_cast<DelphiIfStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrIfStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
