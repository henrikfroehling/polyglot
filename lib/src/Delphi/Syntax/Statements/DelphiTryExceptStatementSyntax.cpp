#include "Delphi/Syntax/Statements/DelphiTryExceptStatementSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementListSyntax.hpp"
#include "Delphi/Syntax/DelphiExceptClauseSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiTryExceptStatementSyntax::DelphiTryExceptStatementSyntax(ISyntaxToken* tryKeyword,
                                                               DelphiStatementListSyntax* statements,
                                                               DelphiExceptClauseSyntax* exceptClause,
                                                               ISyntaxToken* endKeyword,
                                                               ISyntaxToken* semiColonToken) noexcept
    : DelphiTryStatementSyntax{SyntaxKind::TryExceptStatement, tryKeyword, statements, endKeyword, semiColonToken},
      _pExceptClause{exceptClause}
{
    _position = _pTryKeyword->position();
    adjustWidthAndFlags(_pTryKeyword);
    adjustWidthAndFlags(_pStatements);
    adjustWidthAndFlags(_pExceptClause);
    adjustWidthAndFlags(_pEndKeyword);
    adjustWidthAndFlags(_pSemiColonToken);
}

SyntaxVariant DelphiTryExceptStatementSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pTryKeyword);
        case 1: return SyntaxVariant::asList(_pStatements);
        case 2: return SyntaxVariant::asNode(_pExceptClause);
        case 3: return SyntaxVariant::asToken(_pEndKeyword);
        case 4: return SyntaxVariant::asToken(_pSemiColonToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiTryExceptStatementSyntax* DelphiTryExceptStatementSyntax::create(SyntaxFactory& syntaxFactory,
                                                                       ISyntaxToken* tryKeyword,
                                                                       DelphiStatementListSyntax* statements,
                                                                       DelphiExceptClauseSyntax* exceptClause,
                                                                       ISyntaxToken* endKeyword,
                                                                       ISyntaxToken* semiColonToken) noexcept
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
