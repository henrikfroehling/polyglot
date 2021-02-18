#include "CodeAnalysis/Core/Syntax/Trivia/IfDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>

namespace polyglot::CodeAnalysis
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
    adjustWidthAndFlags(_pIfKeyword);
    adjustWidthAndFlags(_pCondition);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
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

    return static_cast<IfDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrIfDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
