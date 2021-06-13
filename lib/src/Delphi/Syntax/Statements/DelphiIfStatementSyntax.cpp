#include "Delphi/Syntax/Statements/DelphiIfStatementSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/Expressions/DelphiExpressionSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementListSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiIfStatementSyntax::DelphiIfStatementSyntax(ISyntaxToken* ifKeyword,
                                                 DelphiExpressionSyntax* conditionExpression,
                                                 ISyntaxToken* thenKeyword,
                                                 DelphiStatementSyntax* statement,
                                                 DelphiElseClauseSyntax* elseClause) noexcept
    : DelphiStatementSyntax{SyntaxKind::IfStatement},
      _pIfKeyword{ifKeyword},
      _pConditionExpression{conditionExpression},
      _pThenKeyword{thenKeyword},
      _pStatement{statement},
      _pElseClause{elseClause}
{}

SyntaxVariant DelphiIfStatementSyntax::child(pg_size index) const
{
    switch (childCount())
    {
        case 4:
        {
            switch (index)
            {
                case 0: return SyntaxVariant::asToken(_pIfKeyword);
                case 1: return SyntaxVariant::asNode(_pConditionExpression);
                case 2: return SyntaxVariant::asToken(_pThenKeyword);
                case 3: return SyntaxVariant::asNode(_pStatement);
            }
        }
        case 5:
        {
            switch (index)
            {
                case 0: return SyntaxVariant::asToken(_pIfKeyword);
                case 1: return SyntaxVariant::asNode(_pConditionExpression);
                case 2: return SyntaxVariant::asToken(_pThenKeyword);
                case 3: return SyntaxVariant::asNode(_pStatement);
                case 4: return SyntaxVariant::asNode(_pElseClause);
            }
        }
    }

    throw std::out_of_range{"index out of range"};
}

DelphiIfStatementSyntax* DelphiIfStatementSyntax::create(SyntaxFactory& syntaxFactory,
                                                         ISyntaxToken* ifKeyword,
                                                         DelphiExpressionSyntax* conditionExpression,
                                                         ISyntaxToken* thenKeyword,
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
