#include "QualifiedNameExpressionSyntax.hpp"
#include <cassert>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "SimpleNameExpressionSyntax.hpp"

namespace polyglot::Core::Syntax
{

QualifiedNameExpressionSyntax::QualifiedNameExpressionSyntax(NameExpressionSyntax* leftExpression,
                                                             ISyntaxToken* dotToken,
                                                             SimpleNameExpressionSyntax* rightExpression) noexcept
    : NameExpressionSyntax{SyntaxKind::QualifiedNameExpression},
      _pLeftExpression{leftExpression},
      _pDotToken{dotToken},
      _pRightExpression{rightExpression}
{
    _position = _pLeftExpression->position();
    adjustWidthAndFlags(_pLeftExpression);
    _pLeftExpression->setChildNumber(0);
    adjustWidthAndFlags(_pDotToken);
    _pDotToken->setChildNumber(1);
    adjustWidthAndFlags(_pRightExpression);
    _pRightExpression->setChildNumber(2);
}

ISyntaxNode* QualifiedNameExpressionSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pLeftExpression;
        case 1: return _pDotToken;
        case 2: return _pRightExpression;
    }

    throw std::out_of_range{"index out of range"};
}

QualifiedNameExpressionSyntax* QualifiedNameExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                                     NameExpressionSyntax* leftExpression,
                                                                     ISyntaxToken* dotToken,
                                                                     SimpleNameExpressionSyntax* rightExpression) noexcept
{
    assert(leftExpression != nullptr);
    assert(dotToken != nullptr);
    assert(dotToken->syntaxKind() == SyntaxKind::DotToken);
    assert(rightExpression != nullptr);

    auto ptrQualifiedNameExpressionSyntax = std::make_unique<QualifiedNameExpressionSyntax>(leftExpression, dotToken, rightExpression);
    return dynamic_cast<QualifiedNameExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrQualifiedNameExpressionSyntax)));
}

} // end namespace polyglot::Core::Syntax
