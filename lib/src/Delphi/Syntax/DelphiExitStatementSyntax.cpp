#include "Delphi/Syntax/DelphiExitStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiExitStatementSyntax::DelphiExitStatementSyntax(Core::Syntax::ISyntaxToken* exitKeyword,
                                                     DelphiParenthesizedExpressionSyntax* expression) noexcept
    : DelphiSimpleStatementSyntax{SyntaxKind::ExitStatement},
      _pExitKeyword{exitKeyword},
      _pExpression{expression}
{}

DelphiExitStatementSyntax* DelphiExitStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                             Core::Syntax::ISyntaxToken* exitKeyword,
                                                             DelphiParenthesizedExpressionSyntax* expression) noexcept
{
    assert(exitKeyword != nullptr);
    assert(exitKeyword->syntaxKind() == SyntaxKind::ExitKeyword);

    auto ptrExitStatementSyntax = std::make_unique<DelphiExitStatementSyntax>(exitKeyword, expression);
    return static_cast<DelphiExitStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrExitStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
