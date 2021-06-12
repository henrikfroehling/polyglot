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
                                                       Core::Syntax::ISyntaxToken* endKeyword) noexcept
    : DelphiStatementSyntax{SyntaxKind::BlockStatement},
      _pBeginKeyword{beginKeyword},
      _pStatementList{statementList},
      _pEndKeyword{endKeyword}
{}

DelphiBlockStatementSyntax* DelphiBlockStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                               Core::Syntax::ISyntaxToken* beginKeyword,
                                                               DelphiStatementListSyntax* statementList,
                                                               Core::Syntax::ISyntaxToken* endKeyword) noexcept
{
    assert(beginKeyword != nullptr);
    assert(beginKeyword->syntaxKind() == SyntaxKind::BeginKeyword);
    assert(statementList != nullptr);
    assert(statementList->syntaxKind() == SyntaxKind::StatementList);
    assert(endKeyword != nullptr);
    assert(endKeyword->syntaxKind() == SyntaxKind::EndKeyword);

    auto ptrBlockStatementSyntax = std::make_unique<DelphiBlockStatementSyntax>(beginKeyword, statementList, endKeyword);
    return static_cast<DelphiBlockStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrBlockStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
