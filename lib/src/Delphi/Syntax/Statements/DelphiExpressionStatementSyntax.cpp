#include "Delphi/Syntax/Statements/DelphiExpressionStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiExpressionStatementSyntax::DelphiExpressionStatementSyntax(DelphiExpressionSyntax* expression,
                                                                 Core::Syntax::ISyntaxToken* semiColonToken) noexcept
    : DelphiStatementSyntax{SyntaxKind::ExpressionStatement},
      _pExpression{expression},
      _pSemiColonToken{semiColonToken}
{}

DelphiExpressionStatementSyntax* DelphiExpressionStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                                         DelphiExpressionSyntax* expression,
                                                                         Core::Syntax::ISyntaxToken* semiColonToken) noexcept
{
    assert(expression != nullptr);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrExpressionStatementSyntax = std::make_unique<DelphiExpressionStatementSyntax>(expression, semiColonToken);
    return static_cast<DelphiExpressionStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrExpressionStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
