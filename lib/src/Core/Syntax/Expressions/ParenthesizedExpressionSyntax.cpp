#include "ParenthesizedExpressionSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Core::Syntax
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
    adjustWidthAndFlags(_pExpression);
    adjustWidthAndFlags(_pCloseParenthesisToken);
}

SyntaxVariant ParenthesizedExpressionSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pOpenParenthesisToken);
        case 1: return SyntaxVariant::asNode(_pExpression);
        case 2: return SyntaxVariant::asToken(_pCloseParenthesisToken);
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

} // end namespace polyglot::Core::Syntax
