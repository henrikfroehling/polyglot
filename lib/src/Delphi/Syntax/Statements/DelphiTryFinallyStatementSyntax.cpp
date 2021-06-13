#include "Delphi/Syntax/Statements/DelphiTryFinallyStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiTryFinallyStatementSyntax::DelphiTryFinallyStatementSyntax(Core::Syntax::ISyntaxToken* tryKeyword,
                                                                 DelphiStatementListSyntax* statements,
                                                                 DelphiFinallyClauseSyntax* finallyClause,
                                                                 Core::Syntax::ISyntaxToken* endKeyword,
                                                                 Core::Syntax::ISyntaxToken* semiColonToken) noexcept
    : DelphiTryStatementSyntax{SyntaxKind::TryFinallyStatement, tryKeyword, statements, endKeyword, semiColonToken},
      _pFinallyClause{finallyClause}
{}

DelphiTryFinallyStatementSyntax* DelphiTryFinallyStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                                         Core::Syntax::ISyntaxToken* tryKeyword,
                                                                         DelphiStatementListSyntax* statements,
                                                                         DelphiFinallyClauseSyntax* finallyClause,
                                                                         Core::Syntax::ISyntaxToken* endKeyword,
                                                                         Core::Syntax::ISyntaxToken* semiColonToken) noexcept
{
    assert(tryKeyword != nullptr);
    assert(tryKeyword->syntaxKind() == SyntaxKind::TryKeyword);
    assert(statements != nullptr);
    assert(finallyClause != nullptr);
    assert(endKeyword != nullptr);
    assert(endKeyword->syntaxKind() == SyntaxKind::EndKeyword);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrTryFinallyStatementSyntax = std::make_unique<DelphiTryFinallyStatementSyntax>(tryKeyword, statements, finallyClause, endKeyword, semiColonToken);
    return static_cast<DelphiTryFinallyStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrTryFinallyStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
