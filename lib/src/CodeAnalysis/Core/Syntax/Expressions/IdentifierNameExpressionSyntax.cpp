#include "CodeAnalysis/Core/Syntax/Expressions/IdentifierNameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

IdentifierNameExpressionSyntax::IdentifierNameExpressionSyntax(ISyntaxToken* identfier) noexcept
    : SimpleNameExpressionSyntax{SyntaxKind::IdentifierNameExpression},
      _pIdentifier{identfier}
{
    _position = _pIdentifier->position();
    adjustWidthAndFlags(_pIdentifier);
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
    return static_cast<IdentifierNameExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrIdentifierNameExpression)));
}

} // end namespace polyglot::CodeAnalysis
