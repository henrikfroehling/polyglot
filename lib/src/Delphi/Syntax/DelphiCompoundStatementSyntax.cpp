#include "Delphi/Syntax/DelphiCompoundStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/DelphiStatementListSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiCompoundStatementSyntax::DelphiCompoundStatementSyntax(Core::Syntax::ISyntaxToken* beginKeyword,
                                                             DelphiStatementListSyntax* statementList,
                                                             Core::Syntax::ISyntaxToken* endKeyword) noexcept
    : DelphiStatementSyntax{SyntaxKind::CompoundStatement},
      _pBeginKeyword{beginKeyword},
      _pStatementList{statementList},
      _pEndKeyword{endKeyword}
{}

DelphiCompoundStatementSyntax* DelphiCompoundStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
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

    auto ptrCompoundStatementSyntax = std::make_unique<DelphiCompoundStatementSyntax>(beginKeyword, statementList, endKeyword);
    return static_cast<DelphiCompoundStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrCompoundStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
