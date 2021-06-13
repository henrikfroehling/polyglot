#include "Delphi/Syntax/Statements/DelphiExceptionHandlerStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiExceptionHandlerStatementSyntax::DelphiExceptionHandlerStatementSyntax(Core::Syntax::ISyntaxToken* onKeyword,
                                                                             DelphiExpressionSyntax* expression,
                                                                             Core::Syntax::ISyntaxToken* doKeyword,
                                                                             DelphiStatementSyntax* statement,
                                                                             Core::Syntax::ISyntaxToken* semiColonToken) noexcept
    : DelphiStatementSyntax{SyntaxKind::ExceptionHandlerExpression},
      _pOnKeyword{onKeyword},
      _pExpression{expression},
      _pDoKeyword{doKeyword},
      _pStatement{statement},
      _pSemiColonToken{semiColonToken}
{}

DelphiExceptionHandlerStatementSyntax* DelphiExceptionHandlerStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                                                     Core::Syntax::ISyntaxToken* onKeyword,
                                                                                     DelphiExpressionSyntax* expression,
                                                                                     Core::Syntax::ISyntaxToken* doKeyword,
                                                                                     DelphiStatementSyntax* statement,
                                                                                     Core::Syntax::ISyntaxToken* semiColonToken) noexcept
{
    assert(onKeyword != nullptr);
    assert(onKeyword->syntaxKind() == SyntaxKind::OnKeyword);
    assert(expression != nullptr);
    assert(doKeyword != nullptr);
    assert(doKeyword->syntaxKind() == SyntaxKind::DoKeyword);
    assert(statement != nullptr);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrExceptionHandlerStatementSyntax = std::make_unique<DelphiExceptionHandlerStatementSyntax>(onKeyword, expression, doKeyword, statement, semiColonToken);
    return static_cast<DelphiExceptionHandlerStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrExceptionHandlerStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
