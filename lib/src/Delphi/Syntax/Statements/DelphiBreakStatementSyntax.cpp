#include "Delphi/Syntax/Statements/DelphiBreakStatementSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiBreakStatementSyntax::DelphiBreakStatementSyntax(ISyntaxToken* breakKeyword,
                                                       ISyntaxToken* semiColonToken) noexcept
    : DelphiStatementSyntax{SyntaxKind::BreakStatement},
      _pBreakKeyword{breakKeyword},
      _pSemiColonToken{semiColonToken}
{
    _position = _pBreakKeyword->position();
    adjustWidthAndFlags(_pBreakKeyword);
    adjustWidthAndFlags(_pSemiColonToken);
}

SyntaxVariant DelphiBreakStatementSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pBreakKeyword);
        case 1: return SyntaxVariant::asToken(_pSemiColonToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiBreakStatementSyntax* DelphiBreakStatementSyntax::create(SyntaxFactory& syntaxFactory,
                                                               ISyntaxToken* breakKeyword,
                                                               ISyntaxToken* semiColonToken) noexcept
{
    assert(breakKeyword != nullptr);
    assert(breakKeyword->syntaxKind() == SyntaxKind::BreakKeyword);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrBreakStatementSyntax = std::make_unique<DelphiBreakStatementSyntax>(breakKeyword, semiColonToken);
    return static_cast<DelphiBreakStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrBreakStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
