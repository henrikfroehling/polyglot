#include "Delphi/Syntax/Statements/DelphiWithStatementSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/Expressions/DelphiExpressionSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiWithStatementSyntax::DelphiWithStatementSyntax(ISyntaxToken* withKeyword,
                                                     DelphiExpressionSyntax* expression,
                                                     ISyntaxToken* doKeyword,
                                                     DelphiStatementSyntax* statement) noexcept
    : DelphiStatementSyntax{SyntaxKind::WithStatement},
      _pWithKeyword{withKeyword},
      _pExpression{expression},
      _pDoKeyword{doKeyword},
      _pStatement{statement}
{}

SyntaxVariant DelphiWithStatementSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pWithKeyword);
        case 1: return SyntaxVariant::asNode(_pExpression);
        case 2: return SyntaxVariant::asToken(_pDoKeyword);
        case 3: return SyntaxVariant::asNode(_pStatement);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiWithStatementSyntax* DelphiWithStatementSyntax::create(SyntaxFactory& syntaxFactory,
                                                             ISyntaxToken* withKeyword,
                                                             DelphiExpressionSyntax* expression,
                                                             ISyntaxToken* doKeyword,
                                                             DelphiStatementSyntax* statement) noexcept
{
    assert(withKeyword != nullptr);
    assert(withKeyword->syntaxKind() == SyntaxKind::WithKeyword);
    assert(expression != nullptr);
    assert(doKeyword != nullptr);
    assert(doKeyword->syntaxKind() == SyntaxKind::DoKeyword);
    assert(statement != nullptr);

    auto ptrWithStatementSyntax = std::make_unique<DelphiWithStatementSyntax>(withKeyword, expression, doKeyword, statement);
    return static_cast<DelphiWithStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrWithStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
