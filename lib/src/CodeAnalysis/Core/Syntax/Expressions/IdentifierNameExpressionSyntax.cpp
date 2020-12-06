#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/IdentifierNameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

IdentifierNameExpressionSyntax::IdentifierNameExpressionSyntax(Ptr<SyntaxToken> identfier) noexcept
    : SimpleNameExpressionSyntax{SyntaxKind::IdentifierNameExpression},
      _ptrIdentifier{identfier}
{}

Ptr<IdentifierNameExpressionSyntax> IdentifierNameExpressionSyntax::create(Ptr<SyntaxToken> identifier) noexcept
{
    assert(identifier != nullptr);
    assert(identifier->syntaxKind() == SyntaxKind::IdentifierToken);

    auto ptrIdentifierNameExpression = std::make_unique<IdentifierNameExpressionSyntax>(identifier);
    return static_cast<IdentifierNameExpressionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrIdentifierNameExpression)));
}

} // end namespace polyglot::CodeAnalysis
