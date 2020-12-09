#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/IfDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

IfDirectiveTriviaSyntax::IfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                 SyntaxToken* startToken,
                                                 SyntaxToken* ifKeyword,
                                                 ExpressionSyntax* condition,
                                                 SyntaxToken* endOfDirectiveToken,
                                                 bool isActive,
                                                 bool isBranchTaken,
                                                 bool conditionValue) noexcept
    : ConditionalDirectiveTriviaSyntax{syntaxKind},
      _ptrStartToken{startToken},
      _ptrIfKeyword{ifKeyword},
      _ptrCondition{condition},
      _ptrEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive},
      _isBranchTaken{isBranchTaken},
      _conditionValue{conditionValue}
{}

IfDirectiveTriviaSyntax* IfDirectiveTriviaSyntax::create(SyntaxToken* startToken,
                                                         SyntaxToken* ifKeyword,
                                                         ExpressionSyntax* condition,
                                                         SyntaxToken* endOfDirectiveToken,
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

    return static_cast<IfDirectiveTriviaSyntax*>(SyntaxPool::addSyntaxTrivia(std::move(ptrIfDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
