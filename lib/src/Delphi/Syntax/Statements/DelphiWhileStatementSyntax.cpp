#include "Delphi/Syntax/Statements/DelphiWhileStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiWhileStatementSyntax::DelphiWhileStatementSyntax(Core::Syntax::ISyntaxToken* whileKeyword,
                                                       DelphiExpressionSyntax* expression,
                                                       Core::Syntax::ISyntaxToken* doKeyword,
                                                       DelphiStatementSyntax* statement) noexcept
    : DelphiStatementSyntax{SyntaxKind::WhileStatement},
      _pWhileKeyword{whileKeyword},
      _pExpression{expression},
      _pDoKeyword{doKeyword},
      _pStatement{statement}
{}

DelphiWhileStatementSyntax* DelphiWhileStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                               Core::Syntax::ISyntaxToken* whileKeyword,
                                                               DelphiExpressionSyntax* expression,
                                                               Core::Syntax::ISyntaxToken* doKeyword,
                                                               DelphiStatementSyntax* statement) noexcept
{
    assert(whileKeyword != nullptr);
    assert(whileKeyword->syntaxKind() == SyntaxKind::WhileKeyword);
    assert(expression != nullptr);
    assert(doKeyword != nullptr);
    assert(doKeyword->syntaxKind() == SyntaxKind::DoKeyword);
    assert(statement != nullptr);

    auto ptrWhileStatementSyntax = std::make_unique<DelphiWhileStatementSyntax>(whileKeyword, expression, doKeyword, statement);
    return static_cast<DelphiWhileStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrWhileStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
