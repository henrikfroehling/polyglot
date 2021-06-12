#include "Delphi/Syntax/Statements/DelphiWithStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiWithStatementSyntax::DelphiWithStatementSyntax(Core::Syntax::ISyntaxToken* withKeyword,
                                                     DelphiExpressionSyntax* expression,
                                                     Core::Syntax::ISyntaxToken* doKeyword,
                                                     DelphiStatementSyntax* statement) noexcept
    : DelphiStatementSyntax{SyntaxKind::WithStatement},
      _pWithKeyword{withKeyword},
      _pExpression{expression},
      _pDoKeyword{doKeyword},
      _pStatement{statement}
{}

DelphiWithStatementSyntax* DelphiWithStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                             Core::Syntax::ISyntaxToken* withKeyword,
                                                             DelphiExpressionSyntax* expression,
                                                             Core::Syntax::ISyntaxToken* doKeyword,
                                                             DelphiStatementSyntax* statement) noexcept
{
    assert(withKeyword != nullptr);
    assert(withKeyword->syntaxKind() == SyntaxKind::WithKeyword);
    assert(expression != nullptr);
    assert(doKeyword != nullptr);
    assert(doKeyword->syntaxKind() == SyntaxKind::DoKeyword);
    assert(statement != nullptr);

    auto ptrWithStatementSyntax = std::make_unique<DelphiWithStatementSyntax>(withKeyword, expression, doKeyword, statement);
    return static_cast<DelphiWithStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrWithStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
