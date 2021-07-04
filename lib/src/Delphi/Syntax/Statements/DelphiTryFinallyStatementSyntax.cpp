#include "Delphi/Syntax/Statements/DelphiTryFinallyStatementSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementListSyntax.hpp"
#include "Delphi/Syntax/DelphiFinallyClauseSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiTryFinallyStatementSyntax::DelphiTryFinallyStatementSyntax(ISyntaxToken* tryKeyword,
                                                                 DelphiStatementListSyntax* statements,
                                                                 DelphiFinallyClauseSyntax* finallyClause,
                                                                 ISyntaxToken* endKeyword,
                                                                 ISyntaxToken* semiColonToken) noexcept
    : DelphiTryStatementSyntax{SyntaxKind::TryFinallyStatement, tryKeyword, statements, endKeyword, semiColonToken},
      _pFinallyClause{finallyClause}
{
    _position = _pTryKeyword->position();
    adjustWidthAndFlags(_pTryKeyword);
    adjustWidthAndFlags(_pStatements);
    adjustWidthAndFlags(_pFinallyClause);
    adjustWidthAndFlags(_pEndKeyword);
    adjustWidthAndFlags(_pSemiColonToken);
}

SyntaxVariant DelphiTryFinallyStatementSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pTryKeyword);
        case 1: return SyntaxVariant::asList(_pStatements);
        case 2: return SyntaxVariant::asNode(_pFinallyClause);
        case 3: return SyntaxVariant::asToken(_pEndKeyword);
        case 4: return SyntaxVariant::asToken(_pSemiColonToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiTryFinallyStatementSyntax* DelphiTryFinallyStatementSyntax::create(SyntaxFactory& syntaxFactory,
                                                                         ISyntaxToken* tryKeyword,
                                                                         DelphiStatementListSyntax* statements,
                                                                         DelphiFinallyClauseSyntax* finallyClause,
                                                                         ISyntaxToken* endKeyword,
                                                                         ISyntaxToken* semiColonToken) noexcept
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
