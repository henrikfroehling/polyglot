#include "Delphi/Syntax/Expressions/DelphiIdentifierNameExpressionSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiIdentifierNameExpressionSyntax::DelphiIdentifierNameExpressionSyntax(ISyntaxToken* identfier) noexcept
    : DelphiSimpleNameExpressionSyntax{SyntaxKind::IdentifierNameExpression},
      _pIdentifier{identfier}
{
    _position = _pIdentifier->position();
    adjustWidthAndFlags(_pIdentifier);
}

SyntaxVariant DelphiIdentifierNameExpressionSyntax::child(pg_size index) const
{
    if (index == 0)
        return SyntaxVariant::asToken(_pIdentifier);

    throw std::out_of_range{"index out of range"};
}

DelphiIdentifierNameExpressionSyntax* DelphiIdentifierNameExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                                                   ISyntaxToken* identifier) noexcept
{
    assert(identifier != nullptr);
    assert(identifier->syntaxKind() == SyntaxKind::IdentifierToken);

    auto ptrIdentifierNameExpression = std::make_unique<DelphiIdentifierNameExpressionSyntax>(identifier);
    return static_cast<DelphiIdentifierNameExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrIdentifierNameExpression)));
}

} // end namespace polyglot::Delphi::Syntax
