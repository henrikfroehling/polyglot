#include "Delphi/Syntax/Statements/DelphiExitStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiExitStatementSyntax::DelphiExitStatementSyntax(Core::Syntax::ISyntaxToken* exitKeyword,
                                                     Core::Syntax::ISyntaxToken* semiColonToken,
                                                     DelphiParenthesizedExpressionSyntax* expression) noexcept
    : DelphiStatementSyntax{SyntaxKind::ExitStatement},
      _pExitKeyword{exitKeyword},
      _pSemiColonToken{semiColonToken},
      _pExpression{expression}
{}

DelphiExitStatementSyntax* DelphiExitStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                             Core::Syntax::ISyntaxToken* exitKeyword,
                                                             Core::Syntax::ISyntaxToken* semiColonToken,
                                                             DelphiParenthesizedExpressionSyntax* expression) noexcept
{
    assert(exitKeyword != nullptr);
    assert(exitKeyword->syntaxKind() == SyntaxKind::ExitKeyword);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrExitStatementSyntax = std::make_unique<DelphiExitStatementSyntax>(exitKeyword, semiColonToken, expression);
    return static_cast<DelphiExitStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrExitStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
