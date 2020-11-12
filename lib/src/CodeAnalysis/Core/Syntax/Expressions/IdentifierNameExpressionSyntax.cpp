#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/IdentifierNameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

IdentifierNameExpressionSyntax::IdentifierNameExpressionSyntax(SyntaxTokenPtr identfier) noexcept
    : SimpleNameExpressionSyntax{SyntaxKind::IdentifierNameExpression},
      _ptrIdentifier{std::move(identfier)}
{}

IdentifierNameExpressionSyntaxPtr IdentifierNameExpressionSyntax::Create(SyntaxTokenPtr identifier) noexcept
{
    assert(identifier != nullptr);
    assert(identifier->syntaxKind() == SyntaxKind::IdentifierToken);
    return std::make_shared<IdentifierNameExpressionSyntax>(std::move(identifier));
}

} // end namespace polyglot::CodeAnalysis
