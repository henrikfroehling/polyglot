#include "Core/Syntax/Expressions/LiteralExpressionSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Core::Syntax
{

LiteralExpressionSyntax::LiteralExpressionSyntax(SyntaxKind syntaxKind,
                                                 ISyntaxToken* literal) noexcept
    : ExpressionSyntax{syntaxKind},
      _pLiteral{literal}
{
    _position = _pLiteral->position();
    adjustWidthAndFlags(_pLiteral);
}

SyntaxVariant LiteralExpressionSyntax::child(pg_size index) const
{
    if (index == 0)
        return SyntaxVariant::asToken(_pLiteral);

    throw std::out_of_range{"index out of range"};
}

LiteralExpressionSyntax* LiteralExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                         SyntaxKind syntaxKind,
                                                         ISyntaxToken* literal) noexcept
{
    assert(literal != nullptr);
    auto ptrLiteralExpression = std::make_unique<LiteralExpressionSyntax>(syntaxKind, literal);
    return static_cast<LiteralExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrLiteralExpression)));
}

} // end namespace polyglot::Core::Syntax
