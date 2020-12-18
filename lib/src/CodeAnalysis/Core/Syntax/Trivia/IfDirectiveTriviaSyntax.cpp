#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/IfDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include <cassert>
#include <memory>

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
      _pStartToken{startToken},
      _pIfKeyword{ifKeyword},
      _pCondition{condition},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive},
      _isBranchTaken{isBranchTaken},
      _conditionValue{conditionValue}
{
    _position = _pStartToken->position();
}

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