#include "Delphi/Syntax/Statements/DelphiRepeatStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiRepeatStatementSyntax::DelphiRepeatStatementSyntax(Core::Syntax::ISyntaxToken* repeatKeyword,
                                                         DelphiStatementSyntax* statement,
                                                         Core::Syntax::ISyntaxToken* untilKeyword,
                                                         DelphiExpressionSyntax* expression,
                                                         Core::Syntax::ISyntaxToken* semiColonToken) noexcept
    : DelphiStatementSyntax{SyntaxKind::RepeatStatement},
      _pRepeatKeyword{repeatKeyword},
      _pStatement{statement},
      _pUntilKeyword{untilKeyword},
      _pExpression{expression},
      _pSemiColonToken{semiColonToken}
{}

DelphiRepeatStatementSyntax* DelphiRepeatStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                                 Core::Syntax::ISyntaxToken* repeatKeyword,
                                                                 DelphiStatementSyntax* statement,
                                                                 Core::Syntax::ISyntaxToken* untilKeyword,
                                                                 DelphiExpressionSyntax* expression,
                                                                 Core::Syntax::ISyntaxToken* semiColonToken) noexcept
{
    assert(repeatKeyword != nullptr);
    assert(repeatKeyword->syntaxKind() == SyntaxKind::RepeatKeyword);
    assert(statement != nullptr);
    assert(untilKeyword != nullptr);
    assert(untilKeyword->syntaxKind() == SyntaxKind::UntilKeyword);
    assert(expression != nullptr);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrRepeatStatementSyntax = std::make_unique<DelphiRepeatStatementSyntax>(repeatKeyword, statement, untilKeyword, expression, semiColonToken);
    return static_cast<DelphiRepeatStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrRepeatStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
