#include "Delphi/Syntax/Statements/DelphiRaiseStatementSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/Expressions/DelphiExpressionSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiRaiseStatementSyntax::DelphiRaiseStatementSyntax(ISyntaxToken* raiseKeyword,
                                                       ISyntaxToken* semiColonToken,
                                                       DelphiExpressionSyntax* expression) noexcept
    : DelphiStatementSyntax{SyntaxKind::RaiseStatement},
      _pRaiseKeyword{raiseKeyword},
      _pSemiColonToken{semiColonToken},
      _pExpression{expression}
{
    _position = _pRaiseKeyword->position();
    adjustWidthAndFlags(_pRaiseKeyword);

    if (_pExpression != nullptr)
        adjustWidthAndFlags(_pExpression);

    adjustWidthAndFlags(_pSemiColonToken);
}

SyntaxVariant DelphiRaiseStatementSyntax::child(pg_size index) const
{
    switch (childCount())
    {
        case 2:
        {
            switch (index)
            {
                case 0: return SyntaxVariant::asToken(_pRaiseKeyword);
                case 1: return SyntaxVariant::asToken(_pSemiColonToken);
            }
        }
        case 3:
        {
            switch (index)
            {
                case 0: return SyntaxVariant::asToken(_pRaiseKeyword);
                case 1: return SyntaxVariant::asNode(_pExpression);
                case 2: return SyntaxVariant::asToken(_pSemiColonToken);
            }
        }
    }

    throw std::out_of_range{"index out of range"};
}

DelphiRaiseStatementSyntax* DelphiRaiseStatementSyntax::create(SyntaxFactory& syntaxFactory,
                                                               ISyntaxToken* raiseKeyword,
                                                               ISyntaxToken* semiColonToken,
                                                               DelphiExpressionSyntax* expression) noexcept
{
    assert(raiseKeyword != nullptr);
    assert(raiseKeyword->syntaxKind() == SyntaxKind::RaiseKeyword);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrRaiseStatementSyntax = std::make_unique<DelphiRaiseStatementSyntax>(raiseKeyword, semiColonToken, expression);
    return static_cast<DelphiRaiseStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrRaiseStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
