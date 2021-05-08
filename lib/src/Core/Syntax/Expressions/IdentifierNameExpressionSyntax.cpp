#include "IdentifierNameExpressionSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Core::Syntax
{

IdentifierNameExpressionSyntax::IdentifierNameExpressionSyntax(ISyntaxToken* identfier) noexcept
    : SimpleNameExpressionSyntax{SyntaxKind::IdentifierNameExpression},
      _pIdentifier{identfier}
{
    _position = _pIdentifier->position();
    adjustWidthAndFlags(_pIdentifier);
    _pIdentifier->setChildNumber(0);
}

ISyntaxNode* IdentifierNameExpressionSyntax::child(pg_size index) const
{
    if (index == 0)
        return _pIdentifier;

    throw std::out_of_range{"index out of range"};
}

IdentifierNameExpressionSyntax* IdentifierNameExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                                       ISyntaxToken* identifier) noexcept
{
    assert(identifier != nullptr);
    assert(identifier->syntaxKind() == SyntaxKind::IdentifierToken);

    auto ptrIdentifierNameExpression = std::make_unique<IdentifierNameExpressionSyntax>(identifier);
    return dynamic_cast<IdentifierNameExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrIdentifierNameExpression)));
}

} // end namespace polyglot::Core::Syntax
