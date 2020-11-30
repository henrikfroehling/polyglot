#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/ElseIfDirectiveTriviaSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

ElseIfDirectiveTriviaSyntax::ElseIfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                         SharedPtr<SyntaxToken> startToken,
                                                         SharedPtr<SyntaxToken> elseIfKeyword,
                                                         SharedPtr<ExpressionSyntax> condition,
                                                         SharedPtr<SyntaxToken> endOfDirectiveToken,
                                                         bool isActive,
                                                         bool isBranchTaken,
                                                         bool conditionValue) noexcept
    : ConditionalDirectiveTriviaSyntax{syntaxKind},
      _ptrStartToken{std::move(startToken)},
      _ptrElseIfKeyword{std::move(elseIfKeyword)},
      _ptrCondition{std::move(condition)},
      _ptrEndOfDirectiveToken{std::move(endOfDirectiveToken)},
      _isActive{isActive},
      _isBranchTaken{isBranchTaken},
      _conditionValue{conditionValue}
{}

SharedPtr<ElseIfDirectiveTriviaSyntax> ElseIfDirectiveTriviaSyntax::create(SharedPtr<SyntaxToken> startToken,
                                                                           SharedPtr<SyntaxToken> elseIfKeyword,
                                                                           SharedPtr<ExpressionSyntax> condition,
                                                                           SharedPtr<SyntaxToken> endOfDirectiveToken,
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

    return std::make_shared<ElseIfDirectiveTriviaSyntax>(SyntaxKind::ElseIfDirectiveTrivia, std::move(startToken),
                                                         std::move(elseIfKeyword), std::move(condition),
                                                         std::move(endOfDirectiveToken), isActive,
                                                         isBranchTaken, conditionValue);
}

} // end namespace polyglot::CodeAnalysis
