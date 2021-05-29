#include "Delphi/Syntax/Expressions/DelphiLiteralExpressionSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiLiteralExpressionSyntax::DelphiLiteralExpressionSyntax(SyntaxKind syntaxKind,
                                                             ISyntaxToken* literal) noexcept
    : DelphiExpressionSyntax{syntaxKind},
      _pLiteral{literal}
{
    _position = _pLiteral->position();
    adjustWidthAndFlags(_pLiteral);
}

SyntaxVariant DelphiLiteralExpressionSyntax::child(pg_size index) const
{
    if (index == 0)
        return SyntaxVariant::asToken(_pLiteral);

    throw std::out_of_range{"index out of range"};
}

DelphiLiteralExpressionSyntax* DelphiLiteralExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                                     SyntaxKind syntaxKind,
                                                                     ISyntaxToken* literal) noexcept
{
    assert(literal != nullptr);
    auto ptrLiteralExpression = std::make_unique<DelphiLiteralExpressionSyntax>(syntaxKind, literal);
    return static_cast<DelphiLiteralExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrLiteralExpression)));
}

} // end namespace polyglot::Delphi::Syntax
