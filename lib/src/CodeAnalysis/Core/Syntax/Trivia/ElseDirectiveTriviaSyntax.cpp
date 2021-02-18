#include "CodeAnalysis/Core/Syntax/Trivia/ElseDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

ElseDirectiveTriviaSyntax::ElseDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                     ISyntaxToken* startToken,
                                                     ISyntaxToken* elseKeyword,
                                                     ISyntaxToken* endOfDirectiveToken,
                                                     bool isActive,
                                                     bool isBranchTaken) noexcept
    : BranchingDirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pElseKeyword{elseKeyword},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive},
      _isBranchTaken{isBranchTaken}
{
    _position = _pStartToken->position();
    adjustWidthAndFlags(_pStartToken);
    adjustWidthAndFlags(_pElseKeyword);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
}

ISyntaxNode* ElseDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pStartToken;
        case 1: return _pElseKeyword;
        case 2: return _pEndOfDirectiveToken;
    }

    throw std::out_of_range{"index out of range"};
}

ElseDirectiveTriviaSyntax* ElseDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                             ISyntaxToken* startToken,
                                                             ISyntaxToken* elseKeyword,
                                                             ISyntaxToken* endOfDirectiveToken,
                                                             bool isActive,
                                                             bool isBranchTaken) noexcept
{
    assert(startToken != nullptr);
    assert(elseKeyword != nullptr);
    assert(elseKeyword->syntaxKind() == SyntaxKind::ElseDirectiveKeyword);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrElseDirectiveTrivia = std::make_unique<ElseDirectiveTriviaSyntax>(SyntaxKind::ElseDirectiveTrivia, startToken,
                                                                              elseKeyword, endOfDirectiveToken,
                                                                              isActive, isBranchTaken);

    return static_cast<ElseDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrElseDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
