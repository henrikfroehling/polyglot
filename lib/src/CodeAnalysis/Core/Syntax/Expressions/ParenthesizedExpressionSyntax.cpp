#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/ParenthesizedExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

ParenthesizedExpressionSyntax::ParenthesizedExpressionSyntax(SyntaxKind syntaxKind,
                                                             SyntaxToken* openParenthesisToken,
                                                             ExpressionSyntax* expression,
                                                             SyntaxToken* closeParenthesisToken) noexcept
    : ExpressionSyntax{syntaxKind},
      _ptrOpenParenthesisToken{openParenthesisToken},
      _ptrExpression{expression},
      _ptrCloseParenthesisToken{closeParenthesisToken}
{}

ParenthesizedExpressionSyntax* ParenthesizedExpressionSyntax::create(SyntaxToken* openParenthesisToken,
                                                                     ExpressionSyntax* expression,
                                                                     SyntaxToken* closeParenthesisToken) noexcept
{
    assert(openParenthesisToken != nullptr);
    assert(openParenthesisToken->syntaxKind() == SyntaxKind::OpenParenthesisToken);
    assert(expression != nullptr);
    assert(closeParenthesisToken != nullptr);
    assert(closeParenthesisToken->syntaxKind() == SyntaxKind::CloseParenthesisToken);

    auto ptrParenthesizedExpression = std::make_unique<ParenthesizedExpressionSyntax>(SyntaxKind::ParenthesizedExpression, openParenthesisToken,
                                                                                      expression, closeParenthesisToken);

    return static_cast<ParenthesizedExpressionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrParenthesizedExpression)));
}

} // end namespace polyglot::CodeAnalysis
