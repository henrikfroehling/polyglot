#include "Delphi/Syntax/DelphiFinallyClauseSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiFinallyClauseSyntax::DelphiFinallyClauseSyntax(ISyntaxToken* finallyKeyword,
                                                     DelphiStatementListSyntax* statements) noexcept
    : DelphiSyntaxNode{SyntaxKind::FinallyClause},
      _pFinallyKeyword{finallyKeyword},
      _pStatements{statements}
{
    _position = _pFinallyKeyword->position();
    adjustWidthAndFlags(_pFinallyKeyword);
    adjustWidthAndFlags(_pStatements);
}

SyntaxVariant DelphiFinallyClauseSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pFinallyKeyword);
        case 1: return SyntaxVariant::asList(_pStatements);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiFinallyClauseSyntax* DelphiFinallyClauseSyntax::create(SyntaxFactory& syntaxFactory,
                                                             ISyntaxToken* finallyKeyword,
                                                             DelphiStatementListSyntax* statements) noexcept
{
    assert(finallyKeyword != nullptr);
    assert(finallyKeyword->syntaxKind() == SyntaxKind::FinallyKeyword);
    assert(statements != nullptr);

    auto ptrFinallyClauseSyntax = std::make_unique<DelphiFinallyClauseSyntax>(finallyKeyword, statements);
    return static_cast<DelphiFinallyClauseSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrFinallyClauseSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
