#include "Core/Syntax/Expressions/CallExpressionSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Core::Syntax
{

CallExpressionSyntax::CallExpressionSyntax(SyntaxKind syntaxKind,
                                           ISyntaxToken* identifier,
                                           ISyntaxToken* openParenthesisToken,
                                           ExpressionSyntax* argumentExpression,
                                           ISyntaxToken* closeParenthesisToken) noexcept
    : ExpressionSyntax{syntaxKind},
      _pIdentifier{identifier},
      _pOpenParenthesisToken{openParenthesisToken},
      _pArgumentExpression{argumentExpression},
      _pCloseParenthesisToken{closeParenthesisToken}
{
    _position = _pIdentifier->position();
    adjustWidthAndFlags(_pIdentifier);
    adjustWidthAndFlags(_pOpenParenthesisToken);
    adjustWidthAndFlags(_pArgumentExpression);
    adjustWidthAndFlags(_pCloseParenthesisToken);
}

SyntaxVariant CallExpressionSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pIdentifier);
        case 1: return SyntaxVariant::asToken(_pOpenParenthesisToken);
        case 2: return SyntaxVariant::asNode(_pArgumentExpression);
        case 3: return SyntaxVariant::asToken(_pCloseParenthesisToken);
    }

    throw std::out_of_range{"index out of range"};
}

CallExpressionSyntax* CallExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                   SyntaxKind syntaxKind,
                                                   ISyntaxToken* identifier,
                                                   ISyntaxToken* openParenthesisToken,
                                                   ExpressionSyntax* argumentExpression,
                                                   ISyntaxToken* closeParenthesisToken) noexcept
{
    assert(identifier != nullptr);
    assert(identifier->syntaxKind() == SyntaxKind::IdentifierToken);
    assert(openParenthesisToken != nullptr);
    assert(openParenthesisToken->syntaxKind() == SyntaxKind::OpenParenthesisToken);
    assert(argumentExpression != nullptr);
    assert(closeParenthesisToken != nullptr);
    assert(closeParenthesisToken->syntaxKind() == SyntaxKind::CloseParenthesisToken);

    auto ptrCallExpression = std::make_unique<CallExpressionSyntax>(syntaxKind, identifier, openParenthesisToken,
                                                                    argumentExpression, closeParenthesisToken);

    return dynamic_cast<CallExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrCallExpression)));
}

} // end namespace polyglot::Core::Syntax
