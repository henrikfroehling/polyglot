#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/IfDirectiveTriviaSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

IfDirectiveTriviaSyntax::IfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                 SharedPtr<SyntaxToken> startToken,
                                                 SharedPtr<SyntaxToken> ifKeyword,
                                                 SharedPtr<ExpressionSyntax> condition,
                                                 SharedPtr<SyntaxToken> endOfDirectiveToken,
                                                 bool isActive,
                                                 bool isBranchTaken,
                                                 bool conditionValue) noexcept
    : ConditionalDirectiveTriviaSyntax{syntaxKind},
      _ptrStartToken{std::move(startToken)},
      _ptrIfKeyword{std::move(ifKeyword)},
      _ptrCondition{std::move(condition)},
      _ptrEndOfDirectiveToken{std::move(endOfDirectiveToken)},
      _isActive{isActive},
      _isBranchTaken{isBranchTaken},
      _conditionValue{conditionValue}
{}

SharedPtr<IfDirectiveTriviaSyntax> IfDirectiveTriviaSyntax::create(SharedPtr<SyntaxToken> startToken,
                                                                   SharedPtr<SyntaxToken> ifKeyword,
                                                                   SharedPtr<ExpressionSyntax> condition,
                                                                   SharedPtr<SyntaxToken> endOfDirectiveToken,
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

    return std::make_shared<IfDirectiveTriviaSyntax>(SyntaxKind::IfDirectiveTrivia, std::move(startToken),
                                                     std::move(ifKeyword), std::move(condition),
                                                     std::move(endOfDirectiveToken), isActive,
                                                     isBranchTaken, conditionValue);
}

} // end namespace polyglot::CodeAnalysis
