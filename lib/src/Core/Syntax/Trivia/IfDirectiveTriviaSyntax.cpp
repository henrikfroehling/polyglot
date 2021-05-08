#include "IfDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/ExpressionSyntax.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Core::Syntax
{

IfDirectiveTriviaSyntax::IfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                 ISyntaxToken* startToken,
                                                 ISyntaxToken* ifKeyword,
                                                 ExpressionSyntax* condition,
                                                 ISyntaxToken* endOfDirectiveToken,
                                                 bool isActive,
                                                 bool isBranchTaken,
                                                 bool conditionValue) noexcept
    : ConditionalDirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pIfKeyword{ifKeyword},
      _pCondition{condition},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive},
      _isBranchTaken{isBranchTaken},
      _conditionValue{conditionValue}
{
    _position = _pStartToken->position();
    adjustWidthAndFlags(_pStartToken);
    _pStartToken->setChildNumber(0);
    adjustWidthAndFlags(_pIfKeyword);
    _pIfKeyword->setChildNumber(1);
    adjustWidthAndFlags(_pCondition);
    _pCondition->setChildNumber(2);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
    _pEndOfDirectiveToken->setChildNumber(3);
}

ISyntaxNode* IfDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pStartToken;
        case 1: return _pIfKeyword;
        case 2: return _pCondition;
        case 3: return _pEndOfDirectiveToken;
    }

    throw std::out_of_range{"index out of range"};
}

IfDirectiveTriviaSyntax* IfDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                         ISyntaxToken* startToken,
                                                         ISyntaxToken* ifKeyword,
                                                         ExpressionSyntax* condition,
                                                         ISyntaxToken* endOfDirectiveToken,
                                                         bool isActive,
                                                         bool isBranchTaken,
                                                         bool conditionValue) noexcept
{
    assert(startToken != nullptr);
    assert(ifKeyword != nullptr);
    assert(ifKeyword->syntaxKind() == SyntaxKind::IfDirectiveKeyword);
    assert(condition != nullptr);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrIfDirectiveTrivia = std::make_unique<IfDirectiveTriviaSyntax>(SyntaxKind::IfDirectiveTrivia, startToken,
                                                                          ifKeyword, condition, endOfDirectiveToken,
                                                                          isActive, isBranchTaken, conditionValue);

    return dynamic_cast<IfDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrIfDirectiveTrivia)));
}

} // end namespace polyglot::Core::Syntax
