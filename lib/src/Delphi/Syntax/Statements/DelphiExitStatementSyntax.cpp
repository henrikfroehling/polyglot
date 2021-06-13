#include "Delphi/Syntax/Statements/DelphiExitStatementSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiExitStatementSyntax::DelphiExitStatementSyntax(ISyntaxToken* exitKeyword,
                                                     ISyntaxToken* semiColonToken,
                                                     DelphiParenthesizedExpressionSyntax* expression) noexcept
    : DelphiStatementSyntax{SyntaxKind::ExitStatement},
      _pExitKeyword{exitKeyword},
      _pSemiColonToken{semiColonToken},
      _pExpression{expression}
{}

SyntaxVariant DelphiExitStatementSyntax::child(pg_size index) const
{
    switch (childCount())
    {
        case 2:
        {
            switch (index)
            {
                case 0: return SyntaxVariant::asToken(_pExitKeyword);
                case 1: return SyntaxVariant::asToken(_pSemiColonToken);
            }
        }
        case 3:
        {
            switch (index)
            {
                case 0: return SyntaxVariant::asToken(_pExitKeyword);
                case 1: return SyntaxVariant::asNode(_pExpression);
                case 2: return SyntaxVariant::asToken(_pSemiColonToken);
            }
        }
    }

    throw std::out_of_range{"index out of range"};
}

DelphiExitStatementSyntax* DelphiExitStatementSyntax::create(SyntaxFactory& syntaxFactory,
                                                             ISyntaxToken* exitKeyword,
                                                             ISyntaxToken* semiColonToken,
                                                             DelphiParenthesizedExpressionSyntax* expression) noexcept
{
    assert(exitKeyword != nullptr);
    assert(exitKeyword->syntaxKind() == SyntaxKind::ExitKeyword);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrExitStatementSyntax = std::make_unique<DelphiExitStatementSyntax>(exitKeyword, semiColonToken, expression);
    return static_cast<DelphiExitStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrExitStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
