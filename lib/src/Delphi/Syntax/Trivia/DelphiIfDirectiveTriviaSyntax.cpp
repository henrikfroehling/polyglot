#include "Delphi/Syntax/Trivia/DelphiIfDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/ExpressionSyntax.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Core/Syntax/SyntaxNode.hpp"
#include "Core/Syntax/SyntaxToken.hpp"
#include "Delphi/Syntax/Expressions/DelphiExpressionSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiIfDirectiveTriviaSyntax::DelphiIfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                             ISyntaxToken* startToken,
                                                             ISyntaxToken* ifKeyword,
                                                             DelphiExpressionSyntax* condition,
                                                             ISyntaxToken* endOfDirectiveToken,
                                                             bool isActive,
                                                             bool isBranchTaken,
                                                             bool conditionValue) noexcept
    : DelphiConditionalDirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pIfKeyword{ifKeyword},
      _pCondition{condition},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive},
      _isBranchTaken{isBranchTaken},
      _conditionValue{conditionValue}
{
    _position = _pStartToken->position();

    adjustWidth(_pStartToken);
    adjustWidth(_pIfKeyword);
    adjustWidth(_pCondition);
    adjustWidth(_pEndOfDirectiveToken);

    static_cast<SyntaxToken*>(_pStartToken)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pIfKeyword)->setTriviaParent(this);
    static_cast<SyntaxNode*>(_pCondition)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pEndOfDirectiveToken)->setTriviaParent(this);
}

SyntaxVariant DelphiIfDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pStartToken);
        case 1: return SyntaxVariant::asToken(_pIfKeyword);
        case 2: return SyntaxVariant::asNode(_pCondition);
        case 3: return SyntaxVariant::asToken(_pEndOfDirectiveToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiIfDirectiveTriviaSyntax* DelphiIfDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                                     ISyntaxToken* startToken,
                                                                     ISyntaxToken* ifKeyword,
                                                                     DelphiExpressionSyntax* condition,
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

    auto ptrIfDirectiveTrivia = std::make_unique<DelphiIfDirectiveTriviaSyntax>(SyntaxKind::IfDirectiveTrivia, startToken,
                                                                                ifKeyword, condition, endOfDirectiveToken,
                                                                                isActive, isBranchTaken, conditionValue);

    return static_cast<DelphiIfDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrIfDirectiveTrivia)));
}

} // end namespace polyglot::Delphi::Syntax
