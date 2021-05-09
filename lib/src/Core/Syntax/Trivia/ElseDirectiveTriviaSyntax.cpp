#include "ElseDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Core::Syntax
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
    adjustWidth(_pStartToken);
    adjustWidth(_pElseKeyword);
    adjustWidth(_pEndOfDirectiveToken);
}

SyntaxNodeOrToken ElseDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxNodeOrToken::asToken(_pStartToken);
        case 1: return SyntaxNodeOrToken::asToken(_pElseKeyword);
        case 2: return SyntaxNodeOrToken::asToken(_pEndOfDirectiveToken);
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

    return dynamic_cast<ElseDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrElseDirectiveTrivia)));
}

} // end namespace polyglot::Core::Syntax
