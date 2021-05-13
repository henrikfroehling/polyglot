#include "Delphi/Syntax/Trivia/DelphiElseDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiElseDirectiveTriviaSyntax::DelphiElseDirectiveTriviaSyntax(SyntaxKind syntaxKind,
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

SyntaxVariant DelphiElseDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pStartToken);
        case 1: return SyntaxVariant::asToken(_pElseKeyword);
        case 2: return SyntaxVariant::asToken(_pEndOfDirectiveToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiElseDirectiveTriviaSyntax* DelphiElseDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
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

    auto ptrElseDirectiveTrivia = std::make_unique<DelphiElseDirectiveTriviaSyntax>(SyntaxKind::ElseDirectiveTrivia, startToken,
                                                                                    elseKeyword, endOfDirectiveToken,
                                                                                    isActive, isBranchTaken);

    return dynamic_cast<DelphiElseDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrElseDirectiveTrivia)));
}

} // end namespace polyglot::Delphi::Syntax
