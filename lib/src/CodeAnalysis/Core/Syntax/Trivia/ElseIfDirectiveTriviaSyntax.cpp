#include "CodeAnalysis/Core/Syntax/Trivia/ElseIfDirectiveTriviaSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

ElseIfDirectiveTriviaSyntax::ElseIfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                         LanguageSyntaxToken* startToken,
                                                         LanguageSyntaxToken* elseIfKeyword,
                                                         ExpressionSyntax* condition,
                                                         LanguageSyntaxToken* endOfDirectiveToken,
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
    adjustWidthAndFlags(_pElseIfKeyword);
    adjustWidthAndFlags(_pCondition);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
}

ElseIfDirectiveTriviaSyntax* ElseIfDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                                 LanguageSyntaxToken* startToken,
                                                                 LanguageSyntaxToken* elseIfKeyword,
                                                                 ExpressionSyntax* condition,
                                                                 LanguageSyntaxToken* endOfDirectiveToken,
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

    return static_cast<ElseIfDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrElseIfDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
