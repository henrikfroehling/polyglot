#include "Delphi/Syntax/Statements/DelphiForToStatementSyntax.hpp"
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

DelphiForToStatementSyntax::DelphiForToStatementSyntax(ISyntaxToken* forKeyword,
                                                       DelphiExpressionSyntax* initialValueExpression,
                                                       ISyntaxToken* toOrDownToKeyword,
                                                       DelphiExpressionSyntax* finalValueExpression,
                                                       ISyntaxToken* doKeyword,
                                                       DelphiStatementSyntax* statement) noexcept
    : DelphiForStatementSyntax{SyntaxKind::ForToStatement, forKeyword, doKeyword, statement},
      _pInitialValueExpression{initialValueExpression},
      _pToOrDownToKeyword{toOrDownToKeyword},
      _pFinalValueExpression{finalValueExpression}
{
    _position = _pForKeyword->position();
    adjustWidthAndFlags(_pForKeyword);
    adjustWidthAndFlags(_pInitialValueExpression);
    adjustWidthAndFlags(_pToOrDownToKeyword);
    adjustWidthAndFlags(_pFinalValueExpression);
    adjustWidthAndFlags(_pDoKeyword);
    adjustWidthAndFlags(_pStatement);
}

SyntaxVariant DelphiForToStatementSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pForKeyword);
        case 1: return SyntaxVariant::asNode(_pInitialValueExpression);
        case 2: return SyntaxVariant::asToken(_pToOrDownToKeyword);
        case 3: return SyntaxVariant::asNode(_pFinalValueExpression);
        case 4: return SyntaxVariant::asToken(_pDoKeyword);
        case 5: return SyntaxVariant::asNode(_pStatement);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiForToStatementSyntax* DelphiForToStatementSyntax::create(SyntaxFactory& syntaxFactory,
                                                               ISyntaxToken* forKeyword,
                                                               DelphiExpressionSyntax* initialValueExpression,
                                                               ISyntaxToken* toOrDownToKeyword,
                                                               DelphiExpressionSyntax* finalValueExpression,
                                                               ISyntaxToken* doKeyword,
                                                               DelphiStatementSyntax* statement) noexcept
{
    assert(forKeyword != nullptr);
    assert(forKeyword->syntaxKind() == SyntaxKind::ForKeyword);
    assert(initialValueExpression != nullptr);
    assert(toOrDownToKeyword != nullptr);
    assert(toOrDownToKeyword->syntaxKind() == SyntaxKind::ToKeyword || toOrDownToKeyword->syntaxKind() == SyntaxKind::DownToKeyword);
    assert(finalValueExpression != nullptr);
    assert(doKeyword != nullptr);
    assert(doKeyword->syntaxKind() == SyntaxKind::DoKeyword);
    assert(statement != nullptr);

    auto ptrForToStatementSyntax = std::make_unique<DelphiForToStatementSyntax>(forKeyword, initialValueExpression, toOrDownToKeyword,
                                                                                finalValueExpression, doKeyword, statement);

    return static_cast<DelphiForToStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrForToStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
