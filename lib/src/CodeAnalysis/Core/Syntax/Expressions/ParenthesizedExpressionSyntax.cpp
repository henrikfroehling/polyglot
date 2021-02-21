#include "CodeAnalysis/Core/Syntax/Expressions/ParenthesizedExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

ParenthesizedExpressionSyntax::ParenthesizedExpressionSyntax(SyntaxKind syntaxKind,
                                                             ISyntaxToken* openParenthesisToken,
                                                             ExpressionSyntax* expression,
                                                             ISyntaxToken* closeParenthesisToken) noexcept
    : ExpressionSyntax{syntaxKind},
      _pOpenParenthesisToken{openParenthesisToken},
      _pExpression{expression},
      _pCloseParenthesisToken{closeParenthesisToken}
{
    _position = _pOpenParenthesisToken->position();
    adjustWidthAndFlags(_pOpenParenthesisToken);
    _pOpenParenthesisToken->setChildNumber(0);
    adjustWidthAndFlags(_pExpression);
    _pExpression->setChildNumber(1);
    adjustWidthAndFlags(_pCloseParenthesisToken);
    _pCloseParenthesisToken->setChildNumber(2);
}

ISyntaxNode* ParenthesizedExpressionSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pOpenParenthesisToken;
        case 1: return _pExpression;
        case 2: return _pCloseParenthesisToken;
    }

    throw std::out_of_range{"index out of range"};
}

ParenthesizedExpressionSyntax* ParenthesizedExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                                     ISyntaxToken* openParenthesisToken,
                                                                     ExpressionSyntax* expression,
                                                                     ISyntaxToken* closeParenthesisToken) noexcept
{
    assert(openParenthesisToken != nullptr);
    assert(openParenthesisToken->syntaxKind() == SyntaxKind::OpenParenthesisToken);
    assert(expression != nullptr);
    assert(closeParenthesisToken != nullptr);
    assert(closeParenthesisToken->syntaxKind() == SyntaxKind::CloseParenthesisToken);

    auto ptrParenthesizedExpression = std::make_unique<ParenthesizedExpressionSyntax>(SyntaxKind::ParenthesizedExpression, openParenthesisToken,
                                                                                      expression, closeParenthesisToken);

    return dynamic_cast<ParenthesizedExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrParenthesizedExpression)));
}

} // end namespace polyglot::CodeAnalysis
