#include "ElseIfDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/ExpressionSyntax.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Core::Syntax
{

ElseIfDirectiveTriviaSyntax::ElseIfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                         ISyntaxToken* startToken,
                                                         ISyntaxToken* elseIfKeyword,
                                                         ExpressionSyntax* condition,
                                                         ISyntaxToken* endOfDirectiveToken,
                                                         bool isActive,
                                                         bool isBranchTaken,
                                                         bool conditionValue) noexcept
    : ConditionalDirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pElseIfKeyword{elseIfKeyword},
      _pCondition{condition},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive},
      _isBranchTaken{isBranchTaken},
      _conditionValue{conditionValue}
{
    _position = _pStartToken->position();
    adjustWidth(_pStartToken);
    adjustWidth(_pElseIfKeyword);
    adjustWidth(_pCondition);
    adjustWidth(_pEndOfDirectiveToken);
}

SyntaxVariant ElseIfDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pStartToken);
        case 1: return SyntaxVariant::asToken(_pElseIfKeyword);
        case 2: return SyntaxVariant::asNode(_pCondition);
        case 3: return SyntaxVariant::asToken(_pEndOfDirectiveToken);
    }

    throw std::out_of_range{"index out of range"};
}

ElseIfDirectiveTriviaSyntax* ElseIfDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                                 ISyntaxToken* startToken,
                                                                 ISyntaxToken* elseIfKeyword,
                                                                 ExpressionSyntax* condition,
                                                                 ISyntaxToken* endOfDirectiveToken,
                                                                 bool isActive,
                                                                 bool isBranchTaken,
                                                                 bool conditionValue) noexcept
{
    assert(startToken != nullptr);
    assert(elseIfKeyword != nullptr);
    assert(elseIfKeyword->syntaxKind() == SyntaxKind::ElseIfDirectiveKeyword);
    assert(condition != nullptr);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrElseIfDirectiveTrivia = std::make_unique<ElseIfDirectiveTriviaSyntax>(SyntaxKind::ElseIfDirectiveTrivia, startToken,
                                                                                  elseIfKeyword, condition, endOfDirectiveToken,
                                                                                  isActive, isBranchTaken, conditionValue);

    return dynamic_cast<ElseIfDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrElseIfDirectiveTrivia)));
}

} // end namespace polyglot::Core::Syntax
