#include "Delphi/Syntax/Statements/DelphiTryExceptStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiTryExceptStatementSyntax::DelphiTryExceptStatementSyntax(Core::Syntax::ISyntaxToken* tryKeyword,
                                                               DelphiStatementListSyntax* statements,
                                                               DelphiExceptClauseSyntax* exceptClause,
                                                               Core::Syntax::ISyntaxToken* endKeyword,
                                                               Core::Syntax::ISyntaxToken* semiColonToken) noexcept
    : DelphiTryStatementSyntax{SyntaxKind::TryExceptStatement, tryKeyword, statements, endKeyword, semiColonToken},
      _pExceptClause{exceptClause}
{}

DelphiTryExceptStatementSyntax* DelphiTryExceptStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                                       Core::Syntax::ISyntaxToken* tryKeyword,
                                                                       DelphiStatementListSyntax* statements,
                                                                       DelphiExceptClauseSyntax* exceptClause,
                                                                       Core::Syntax::ISyntaxToken* endKeyword,
                                                                       Core::Syntax::ISyntaxToken* semiColonToken) noexcept
{
    assert(tryKeyword != nullptr);
    assert(tryKeyword->syntaxKind() == SyntaxKind::TryKeyword);
    assert(statements != nullptr);
    assert(exceptClause != nullptr);
    assert(endKeyword != nullptr);
    assert(endKeyword->syntaxKind() == SyntaxKind::EndKeyword);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrTryExceptStatementSyntax = std::make_unique<DelphiTryExceptStatementSyntax>(tryKeyword, statements, exceptClause, endKeyword, semiColonToken);
    return static_cast<DelphiTryExceptStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrTryExceptStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
