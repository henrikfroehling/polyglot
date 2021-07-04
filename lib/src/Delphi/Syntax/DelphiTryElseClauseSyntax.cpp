#include "Delphi/Syntax/DelphiTryElseClauseSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiTryElseClauseSyntax::DelphiTryElseClauseSyntax(ISyntaxToken* elseKeyword,
                                                     DelphiStatementListSyntax* statements) noexcept
    : DelphiSyntaxNode{SyntaxKind::TryElseClause},
      _pElseKeyword{elseKeyword},
      _pStatements{statements}
{
    _position = _pElseKeyword->position();
    adjustWidthAndFlags(_pElseKeyword);
    adjustWidthAndFlags(_pStatements);
}

SyntaxVariant DelphiTryElseClauseSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pElseKeyword);
        case 1: return SyntaxVariant::asList(_pStatements);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiTryElseClauseSyntax* DelphiTryElseClauseSyntax::create(SyntaxFactory& syntaxFactory,
                                                             ISyntaxToken* elseKeyword,
                                                             DelphiStatementListSyntax* statements) noexcept
{
    assert(elseKeyword != nullptr);
    assert(elseKeyword->syntaxKind() == SyntaxKind::ElseKeyword);
    assert(statements != nullptr);

    auto ptrTryElseClauseSyntax = std::make_unique<DelphiTryElseClauseSyntax>(elseKeyword, statements);
    return static_cast<DelphiTryElseClauseSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrTryElseClauseSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
