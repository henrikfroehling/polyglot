#include "Delphi/Syntax/Statements/DelphiBlockStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementListSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiBlockStatementSyntax::DelphiBlockStatementSyntax(Core::Syntax::ISyntaxToken* beginKeyword,
                                                       DelphiStatementListSyntax* statementList,
                                                       Core::Syntax::ISyntaxToken* endKeyword,
                                                       Core::Syntax::ISyntaxToken* semiColonToken) noexcept
    : DelphiStatementSyntax{SyntaxKind::BlockStatement},
      _pBeginKeyword{beginKeyword},
      _pStatementList{statementList},
      _pEndKeyword{endKeyword},
      _pSemiColonToken{semiColonToken}
{}

DelphiBlockStatementSyntax* DelphiBlockStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                               Core::Syntax::ISyntaxToken* beginKeyword,
                                                               DelphiStatementListSyntax* statementList,
                                                               Core::Syntax::ISyntaxToken* endKeyword,
                                                               Core::Syntax::ISyntaxToken* semiColonToken) noexcept
{
    assert(beginKeyword != nullptr);
    assert(beginKeyword->syntaxKind() == SyntaxKind::BeginKeyword);
    assert(statementList != nullptr);
    assert(statementList->syntaxKind() == SyntaxKind::StatementList);
    assert(endKeyword != nullptr);
    assert(endKeyword->syntaxKind() == SyntaxKind::EndKeyword);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrBlockStatementSyntax = std::make_unique<DelphiBlockStatementSyntax>(beginKeyword, statementList, endKeyword, semiColonToken);
    return static_cast<DelphiBlockStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrBlockStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
