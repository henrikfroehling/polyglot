#include "Delphi/Syntax/Statements/DelphiExpressionStatementSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiExpressionStatementSyntax::DelphiExpressionStatementSyntax(DelphiExpressionSyntax* expression,
                                                                 ISyntaxToken* semiColonToken) noexcept
    : DelphiStatementSyntax{SyntaxKind::ExpressionStatement},
      _pExpression{expression},
      _pSemiColonToken{semiColonToken}
{
    _position = _pExpression->position();
    adjustWidthAndFlags(_pExpression);
    adjustWidthAndFlags(_pSemiColonToken);
}

SyntaxVariant DelphiExpressionStatementSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asNode(_pExpression);
        case 1: return SyntaxVariant::asToken(_pSemiColonToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiExpressionStatementSyntax* DelphiExpressionStatementSyntax::create(SyntaxFactory& syntaxFactory,
                                                                         DelphiExpressionSyntax* expression,
                                                                         ISyntaxToken* semiColonToken) noexcept
{
    assert(expression != nullptr);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrExpressionStatementSyntax = std::make_unique<DelphiExpressionStatementSyntax>(expression, semiColonToken);
    return static_cast<DelphiExpressionStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrExpressionStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
