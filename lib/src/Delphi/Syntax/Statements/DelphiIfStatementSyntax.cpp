#include "Delphi/Syntax/Statements/DelphiIfStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementListSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiIfStatementSyntax::DelphiIfStatementSyntax(Core::Syntax::ISyntaxToken* ifKeyword,
                                                 DelphiExpressionSyntax* conditionExpression,
                                                 Core::Syntax::ISyntaxToken* thenKeyword,
                                                 DelphiStatementSyntax* statement,
                                                 DelphiElseClauseSyntax* elseClause) noexcept
    : DelphiStatementSyntax{SyntaxKind::IfStatement},
      _pIfKeyword{ifKeyword},
      _pConditionExpression{conditionExpression},
      _pThenKeyword{thenKeyword},
      _pStatement{statement},
      _pElseClause{elseClause}
{}

DelphiIfStatementSyntax* DelphiIfStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                         Core::Syntax::ISyntaxToken* ifKeyword,
                                                         DelphiExpressionSyntax* conditionExpression,
                                                         Core::Syntax::ISyntaxToken* thenKeyword,
                                                         DelphiStatementSyntax* statement,
                                                         DelphiElseClauseSyntax* elseClause) noexcept
{
    assert(ifKeyword != nullptr);
    assert(ifKeyword->syntaxKind() == SyntaxKind::IfKeyword);
    assert(conditionExpression != nullptr);
    assert(thenKeyword != nullptr);
    assert(thenKeyword->syntaxKind() == SyntaxKind::ThenKeyword);
    assert(statement != nullptr);

    auto ptrIfStatementSyntax = std::make_unique<DelphiIfStatementSyntax>(ifKeyword, conditionExpression, thenKeyword, statement, elseClause);
    return static_cast<DelphiIfStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrIfStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
