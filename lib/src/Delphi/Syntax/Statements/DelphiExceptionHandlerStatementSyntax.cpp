#include "Delphi/Syntax/Statements/DelphiExceptionHandlerStatementSyntax.hpp"
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

DelphiExceptionHandlerStatementSyntax::DelphiExceptionHandlerStatementSyntax(ISyntaxToken* onKeyword,
                                                                             DelphiExpressionSyntax* expression,
                                                                             ISyntaxToken* doKeyword,
                                                                             DelphiStatementSyntax* statement,
                                                                             ISyntaxToken* semiColonToken) noexcept
    : DelphiStatementSyntax{SyntaxKind::ExceptionHandlerExpression},
      _pOnKeyword{onKeyword},
      _pExpression{expression},
      _pDoKeyword{doKeyword},
      _pStatement{statement},
      _pSemiColonToken{semiColonToken}
{
    _position = _pOnKeyword->position();
    adjustWidthAndFlags(_pOnKeyword);
    adjustWidthAndFlags(_pExpression);
    adjustWidthAndFlags(_pDoKeyword);
    adjustWidthAndFlags(_pStatement);
    adjustWidthAndFlags(_pSemiColonToken);
}

SyntaxVariant DelphiExceptionHandlerStatementSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pOnKeyword);
        case 1: return SyntaxVariant::asNode(_pExpression);
        case 2: return SyntaxVariant::asToken(_pDoKeyword);
        case 3: return SyntaxVariant::asNode(_pStatement);
        case 4: return SyntaxVariant::asToken(_pSemiColonToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiExceptionHandlerStatementSyntax* DelphiExceptionHandlerStatementSyntax::create(SyntaxFactory& syntaxFactory,
                                                                                     ISyntaxToken* onKeyword,
                                                                                     DelphiExpressionSyntax* expression,
                                                                                     ISyntaxToken* doKeyword,
                                                                                     DelphiStatementSyntax* statement,
                                                                                     ISyntaxToken* semiColonToken) noexcept
{
    assert(onKeyword != nullptr);
    assert(onKeyword->syntaxKind() == SyntaxKind::OnKeyword);
    assert(expression != nullptr);
    assert(doKeyword != nullptr);
    assert(doKeyword->syntaxKind() == SyntaxKind::DoKeyword);
    assert(statement != nullptr);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrExceptionHandlerStatementSyntax = std::make_unique<DelphiExceptionHandlerStatementSyntax>(onKeyword, expression, doKeyword, statement, semiColonToken);
    return static_cast<DelphiExceptionHandlerStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrExceptionHandlerStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
