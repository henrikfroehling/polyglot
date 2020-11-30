#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/LiteralExpressionSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

LiteralExpressionSyntax::LiteralExpressionSyntax(SyntaxKind syntaxKind,
                                                 SharedPtr<SyntaxToken> token) noexcept
    : ExpressionSyntax{syntaxKind},
      _ptrToken{std::move(token)}
{}

SharedPtr<LiteralExpressionSyntax> LiteralExpressionSyntax::create(SyntaxKind syntaxKind,
                                                                   SharedPtr<SyntaxToken> token) noexcept
{
    assert(token != nullptr);
    return std::make_shared<LiteralExpressionSyntax>(syntaxKind, std::move(token));
}

} // end namespace polyglot::CodeAnalysis
