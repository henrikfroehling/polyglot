#include "Delphi/Syntax/Expressions/DelphiParenthesizedExpressionSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiParenthesizedExpressionSyntax::DelphiParenthesizedExpressionSyntax(SyntaxKind syntaxKind,
                                                                         ISyntaxToken* openParenthesisToken,
                                                                         DelphiExpressionSyntax* expression,
                                                                         ISyntaxToken* closeParenthesisToken) noexcept
    : DelphiExpressionSyntax{syntaxKind},
      _pOpenParenthesisToken{openParenthesisToken},
      _pExpression{expression},
      _pCloseParenthesisToken{closeParenthesisToken}
{
    _position = _pOpenParenthesisToken->position();
    adjustWidthAndFlags(_pOpenParenthesisToken);
    adjustWidthAndFlags(_pExpression);
    adjustWidthAndFlags(_pCloseParenthesisToken);
}

SyntaxVariant DelphiParenthesizedExpressionSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pOpenParenthesisToken);
        case 1: return SyntaxVariant::asNode(_pExpression);
        case 2: return SyntaxVariant::asToken(_pCloseParenthesisToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiParenthesizedExpressionSyntax* DelphiParenthesizedExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                                                 ISyntaxToken* openParenthesisToken,
                                                                                 DelphiExpressionSyntax* expression,
                                                                                 ISyntaxToken* closeParenthesisToken) noexcept
{
    assert(openParenthesisToken != nullptr);
    assert(openParenthesisToken->syntaxKind() == SyntaxKind::OpenParenthesisToken);
    assert(expression != nullptr);
    assert(closeParenthesisToken != nullptr);
    assert(closeParenthesisToken->syntaxKind() == SyntaxKind::CloseParenthesisToken);

    auto ptrParenthesizedExpression = std::make_unique<DelphiParenthesizedExpressionSyntax>(SyntaxKind::ParenthesizedExpression, openParenthesisToken,
                                                                                            expression, closeParenthesisToken);

    return static_cast<DelphiParenthesizedExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrParenthesizedExpression)));
}

} // end namespace polyglot::Delphi::Syntax
