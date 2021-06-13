#include "Delphi/Syntax/Statements/DelphiBlockStatementSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementListSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiBlockStatementSyntax::DelphiBlockStatementSyntax(ISyntaxToken* beginKeyword,
                                                       DelphiStatementListSyntax* statementList,
                                                       ISyntaxToken* endKeyword,
                                                       ISyntaxToken* semiColonToken) noexcept
    : DelphiStatementSyntax{SyntaxKind::BlockStatement},
      _pBeginKeyword{beginKeyword},
      _pStatementList{statementList},
      _pEndKeyword{endKeyword},
      _pSemiColonToken{semiColonToken}
{}

SyntaxVariant DelphiBlockStatementSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pBeginKeyword);
        case 1: return SyntaxVariant::asList(_pStatementList);
        case 2: return SyntaxVariant::asToken(_pEndKeyword);
        case 3: return SyntaxVariant::asToken(_pSemiColonToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiBlockStatementSyntax* DelphiBlockStatementSyntax::create(SyntaxFactory& syntaxFactory,
                                                               ISyntaxToken* beginKeyword,
                                                               DelphiStatementListSyntax* statementList,
                                                               ISyntaxToken* endKeyword,
                                                               ISyntaxToken* semiColonToken) noexcept
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
