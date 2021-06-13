#include "Delphi/Syntax/Statements/DelphiForToStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiForToStatementSyntax::DelphiForToStatementSyntax(Core::Syntax::ISyntaxToken* forKeyword,
                                                       DelphiExpressionSyntax* initialValueExpression,
                                                       Core::Syntax::ISyntaxToken* toOrDownToKeyword,
                                                       DelphiExpressionSyntax* finalValueExpression,
                                                       Core::Syntax::ISyntaxToken* doKeyword,
                                                       DelphiStatementSyntax* statement) noexcept
    : DelphiForStatementSyntax{SyntaxKind::ForToStatement, forKeyword, doKeyword, statement},
      _pInitialValueExpression{initialValueExpression},
      _pToOrDownToKeyword{toOrDownToKeyword},
      _pFinalValueExpression{finalValueExpression}
{}

DelphiForToStatementSyntax* DelphiForToStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                               Core::Syntax::ISyntaxToken* forKeyword,
                                                               DelphiExpressionSyntax* initialValueExpression,
                                                               Core::Syntax::ISyntaxToken* toOrDownToKeyword,
                                                               DelphiExpressionSyntax* finalValueExpression,
                                                               Core::Syntax::ISyntaxToken* doKeyword,
                                                               DelphiStatementSyntax* statement) noexcept
{
    assert(forKeyword != nullptr);
    assert(forKeyword->syntaxKind() == SyntaxKind::ForKeyword);
    assert(initialValueExpression != nullptr);
    assert(toOrDownToKeyword != nullptr);
    assert(toOrDownToKeyword->syntaxKind() == SyntaxKind::ToKeyword || toOrDownToKeyword->syntaxKind() == SyntaxKind::DownToKeyword);
    assert(finalValueExpression != nullptr);
    assert(doKeyword != nullptr);
    assert(doKeyword->syntaxKind() == SyntaxKind::DoKeyword);
    assert(statement != nullptr);

    auto ptrForToStatementSyntax = std::make_unique<DelphiForToStatementSyntax>(forKeyword, initialValueExpression, toOrDownToKeyword,
                                                                                finalValueExpression, doKeyword, statement);

    return static_cast<DelphiForToStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrForToStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
