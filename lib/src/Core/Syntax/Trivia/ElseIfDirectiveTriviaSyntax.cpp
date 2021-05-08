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
    adjustWidthAndFlags(_pStartToken);
    _pStartToken->setChildNumber(0);
    adjustWidthAndFlags(_pElseIfKeyword);
    _pElseIfKeyword->setChildNumber(1);
    adjustWidthAndFlags(_pCondition);
    _pCondition->setChildNumber(2);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
    _pEndOfDirectiveToken->setChildNumber(3);
}

ISyntaxNode* ElseIfDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pStartToken;
        case 1: return _pElseIfKeyword;
        case 2: return _pCondition;
        case 3: return _pEndOfDirectiveToken;
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
