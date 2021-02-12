#include "CodeAnalysis/Core/Syntax/Expressions/CallExpressionSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

CallExpressionSyntax::CallExpressionSyntax(SyntaxKind syntaxKind,
                                           LanguageSyntaxToken* identifier,
                                           LanguageSyntaxToken* openParenthesisToken,
                                           ExpressionSyntax* argumentExpression,
                                           LanguageSyntaxToken* closeParenthesisToken) noexcept
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

LanguageSyntaxNode* CallExpressionSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pIdentifier;
        case 1: return _pOpenParenthesisToken;
        case 2: return _pArgumentExpression;
        case 3: return _pCloseParenthesisToken;
    }

    throw std::out_of_range{"index out of range"};
}

CallExpressionSyntax* CallExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                   SyntaxKind syntaxKind,
                                                   LanguageSyntaxToken* identifier,
                                                   LanguageSyntaxToken* openParenthesisToken,
                                                   ExpressionSyntax* argumentExpression,
                                                   LanguageSyntaxToken* closeParenthesisToken) noexcept
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

    return static_cast<CallExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrCallExpression)));
}

} // end namespace polyglot::CodeAnalysis
