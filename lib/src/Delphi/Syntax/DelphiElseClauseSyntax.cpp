#include "Delphi/Syntax/DelphiElseClauseSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiElseClauseSyntax::DelphiElseClauseSyntax(ISyntaxToken* elseKeyword,
                                               DelphiStatementSyntax* statement) noexcept
    : DelphiSyntaxNode{SyntaxKind::ElseClause},
      _pElseKeyword{elseKeyword},
      _pStatement{statement}
{
    _position = _pElseKeyword->position();
    adjustWidthAndFlags(_pElseKeyword);
    adjustWidthAndFlags(_pStatement);
}

SyntaxVariant DelphiElseClauseSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pElseKeyword);
        case 1: return SyntaxVariant::asNode(_pStatement);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiElseClauseSyntax* DelphiElseClauseSyntax::create(SyntaxFactory& syntaxFactory,
                                                       ISyntaxToken* elseKeyword,
                                                       DelphiStatementSyntax* statement) noexcept
{
    assert(elseKeyword != nullptr);
    assert(elseKeyword->syntaxKind() == SyntaxKind::ElseKeyword);
    assert(statement != nullptr);

    auto ptrElseClauseSyntax = std::make_unique<DelphiElseClauseSyntax>(elseKeyword, statement);
    return static_cast<DelphiElseClauseSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrElseClauseSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
