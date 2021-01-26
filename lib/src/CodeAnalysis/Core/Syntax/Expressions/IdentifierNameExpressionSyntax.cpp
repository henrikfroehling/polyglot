#include "CodeAnalysis/Core/Syntax/Expressions/IdentifierNameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Parser/SyntaxPool.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

IdentifierNameExpressionSyntax::IdentifierNameExpressionSyntax(LanguageSyntaxToken* identfier) noexcept
    : SimpleNameExpressionSyntax{SyntaxKind::IdentifierNameExpression},
      _pIdentifier{identfier}
{
    _position = _pIdentifier->position();
}

IdentifierNameExpressionSyntax* IdentifierNameExpressionSyntax::create(LanguageSyntaxToken* identifier) noexcept
{
    assert(identifier != nullptr);
    assert(identifier->syntaxKind() == SyntaxKind::IdentifierToken);

    auto ptrIdentifierNameExpression = std::make_unique<IdentifierNameExpressionSyntax>(identifier);
    return static_cast<IdentifierNameExpressionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrIdentifierNameExpression)));
}

} // end namespace polyglot::CodeAnalysis
