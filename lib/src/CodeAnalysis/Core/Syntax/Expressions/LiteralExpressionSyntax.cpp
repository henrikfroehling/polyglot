#include "CodeAnalysis/Core/Syntax/Expressions/LiteralExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

LiteralExpressionSyntax::LiteralExpressionSyntax(SyntaxKind syntaxKind,
                                                 ISyntaxToken* literal) noexcept
    : ExpressionSyntax{syntaxKind},
      _pLiteral{literal}
{
    _position = _pLiteral->position();
    adjustWidthAndFlags(_pLiteral);
}

ISyntaxNode* LiteralExpressionSyntax::child(pg_size index) const
{
    if (index == 0)
        return _pLiteral;

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

} // end namespace polyglot::CodeAnalysis
