#include "CodeAnalysis/Core/Syntax/Expressions/QualifiedNameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Core/Syntax/Expressions/SimpleNameExpressionSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

QualifiedNameExpressionSyntax::QualifiedNameExpressionSyntax(NameExpressionSyntax* leftExpression,
                                                             LanguageSyntaxToken* dotToken,
                                                             SimpleNameExpressionSyntax* rightExpression) noexcept
    : NameExpressionSyntax{SyntaxKind::QualifiedNameExpression},
      _pLeftExpression{leftExpression},
      _pDotToken{dotToken},
      _pRightExpression{rightExpression}
{
    _position = _pLeftExpression->position();
    adjustWidthAndFlags(_pLeftExpression);
    adjustWidthAndFlags(_pDotToken);
    adjustWidthAndFlags(_pRightExpression);
}

QualifiedNameExpressionSyntax* QualifiedNameExpressionSyntax::create(NameExpressionSyntax* leftExpression,
                                                                     LanguageSyntaxToken* dotToken,
                                                                     SimpleNameExpressionSyntax* rightExpression) noexcept
{
    assert(leftExpression != nullptr);
    assert(dotToken != nullptr);
    assert(dotToken->syntaxKind() == SyntaxKind::DotToken);
    assert(rightExpression != nullptr);

    auto ptrQualifiedNameExpressionSyntax = std::make_unique<QualifiedNameExpressionSyntax>(leftExpression, dotToken, rightExpression);
    return static_cast<QualifiedNameExpressionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrQualifiedNameExpressionSyntax)));
}

} // end namespace polyglot::CodeAnalysis
