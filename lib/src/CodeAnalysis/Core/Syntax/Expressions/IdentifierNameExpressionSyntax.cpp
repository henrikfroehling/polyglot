#include "CodeAnalysis/Core/Syntax/Expressions/IdentifierNameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
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
    adjustWidthAndFlags(_pIdentifier);
}

IdentifierNameExpressionSyntax* IdentifierNameExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                                       LanguageSyntaxToken* identifier) noexcept
{
    assert(identifier != nullptr);
    assert(identifier->syntaxKind() == SyntaxKind::IdentifierToken);

    auto ptrIdentifierNameExpression = std::make_unique<IdentifierNameExpressionSyntax>(identifier);
    return static_cast<IdentifierNameExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrIdentifierNameExpression)));
}

} // end namespace polyglot::CodeAnalysis
