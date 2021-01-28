#include "CodeAnalysis/Core/Syntax/Expressions/CallExpressionSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <memory>

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
}

CallExpressionSyntax* CallExpressionSyntax::create(SyntaxKind syntaxKind,
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

    return static_cast<CallExpressionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrCallExpression)));
}

} // end namespace polyglot::CodeAnalysis
