#include "Delphi/Syntax/Statements/DelphiRepeatStatementSyntax.hpp"
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

DelphiRepeatStatementSyntax::DelphiRepeatStatementSyntax(ISyntaxToken* repeatKeyword,
                                                         DelphiStatementSyntax* statement,
                                                         ISyntaxToken* untilKeyword,
                                                         DelphiExpressionSyntax* expression,
                                                         ISyntaxToken* semiColonToken) noexcept
    : DelphiStatementSyntax{SyntaxKind::RepeatStatement},
      _pRepeatKeyword{repeatKeyword},
      _pStatement{statement},
      _pUntilKeyword{untilKeyword},
      _pExpression{expression},
      _pSemiColonToken{semiColonToken}
{}

SyntaxVariant DelphiRepeatStatementSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pRepeatKeyword);
        case 1: return SyntaxVariant::asNode(_pStatement);
        case 2: return SyntaxVariant::asToken(_pUntilKeyword);
        case 3: return SyntaxVariant::asNode(_pExpression);
        case 4: return SyntaxVariant::asToken(_pSemiColonToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiRepeatStatementSyntax* DelphiRepeatStatementSyntax::create(SyntaxFactory& syntaxFactory,
                                                                 ISyntaxToken* repeatKeyword,
                                                                 DelphiStatementSyntax* statement,
                                                                 ISyntaxToken* untilKeyword,
                                                                 DelphiExpressionSyntax* expression,
                                                                 ISyntaxToken* semiColonToken) noexcept
{
    assert(repeatKeyword != nullptr);
    assert(repeatKeyword->syntaxKind() == SyntaxKind::RepeatKeyword);
    assert(statement != nullptr);
    assert(untilKeyword != nullptr);
    assert(untilKeyword->syntaxKind() == SyntaxKind::UntilKeyword);
    assert(expression != nullptr);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrRepeatStatementSyntax = std::make_unique<DelphiRepeatStatementSyntax>(repeatKeyword, statement, untilKeyword, expression, semiColonToken);
    return static_cast<DelphiRepeatStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrRepeatStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
