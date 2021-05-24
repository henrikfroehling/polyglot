#include "Delphi/Syntax/DelphiCompoundStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/DelphiStatementListSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiCompoundStatementSyntax::DelphiCompoundStatementSyntax(Core::Syntax::ISyntaxToken* beginToken,
                                                             DelphiStatementListSyntax* statementList,
                                                             Core::Syntax::ISyntaxToken* endToken) noexcept
    : DelphiStatementSyntax{SyntaxKind::CompoundStatement},
      _pBeginToken{beginToken},
      _pStatementList{statementList},
      _pEndToken{endToken}
{}

DelphiCompoundStatementSyntax* DelphiCompoundStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                                     Core::Syntax::ISyntaxToken* beginToken,
                                                                     DelphiStatementListSyntax* statementList,
                                                                     Core::Syntax::ISyntaxToken* endToken) noexcept
{
    assert(beginToken != nullptr);
    assert(beginToken->syntaxKind() == SyntaxKind::BeginKeyword);
    assert(statementList != nullptr);
    assert(statementList->syntaxKind() == SyntaxKind::StatementList);
    assert(endToken != nullptr);
    assert(endToken->syntaxKind() == SyntaxKind::EndKeyword);

    auto ptrCompoundStatementSyntax = std::make_unique<DelphiCompoundStatementSyntax>(beginToken, statementList, endToken);
    return static_cast<DelphiCompoundStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrCompoundStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
