#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/ElseIfDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

ElseIfDirectiveTriviaSyntax::ElseIfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                         Ptr<SyntaxToken> startToken,
                                                         Ptr<SyntaxToken> elseIfKeyword,
                                                         Ptr<ExpressionSyntax> condition,
                                                         Ptr<SyntaxToken> endOfDirectiveToken,
                                                         bool isActive,
                                                         bool isBranchTaken,
                                                         bool conditionValue) noexcept
    : ConditionalDirectiveTriviaSyntax{syntaxKind},
      _ptrStartToken{startToken},
      _ptrElseIfKeyword{elseIfKeyword},
      _ptrCondition{condition},
      _ptrEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive},
      _isBranchTaken{isBranchTaken},
      _conditionValue{conditionValue}
{}

Ptr<ElseIfDirectiveTriviaSyntax> ElseIfDirectiveTriviaSyntax::create(Ptr<SyntaxToken> startToken,
                                                                     Ptr<SyntaxToken> elseIfKeyword,
                                                                     Ptr<ExpressionSyntax> condition,
                                                                     Ptr<SyntaxToken> endOfDirectiveToken,
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

    return static_cast<ElseIfDirectiveTriviaSyntax*>(SyntaxPool::addSyntaxTrivia(std::move(ptrElseIfDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
