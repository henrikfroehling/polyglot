#include "Delphi/Syntax/Trivia/DelphiEndRegionDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Core/Syntax/SyntaxToken.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiEndRegionDirectiveTriviaSyntax::DelphiEndRegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                                           ISyntaxToken* startToken,
                                                                           ISyntaxToken* endRegionKeyword,
                                                                           ISyntaxToken* endOfDirectiveToken,
                                                                           bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pEndRegionKeyword{endRegionKeyword},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _pStartToken->position();

    adjustWidth(_pStartToken);
    adjustWidth(_pEndRegionKeyword);
    adjustWidth(_pEndOfDirectiveToken);

    static_cast<SyntaxToken*>(_pStartToken)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pEndRegionKeyword)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pEndOfDirectiveToken)->setTriviaParent(this);
}

SyntaxVariant DelphiEndRegionDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pStartToken);
        case 1: return SyntaxVariant::asToken(_pEndRegionKeyword);
        case 2: return SyntaxVariant::asToken(_pEndOfDirectiveToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiEndRegionDirectiveTriviaSyntax* DelphiEndRegionDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                                                   ISyntaxToken* startToken,
                                                                                   ISyntaxToken* endRegionKeyword,
                                                                                   ISyntaxToken* endOfDirectiveToken,
                                                                                   bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(endRegionKeyword != nullptr);
    assert(endRegionKeyword->syntaxKind() == SyntaxKind::EndRegionDirectiveKeyword);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrEndRegionDirectiveTrivia = std::make_unique<DelphiEndRegionDirectiveTriviaSyntax>(SyntaxKind::EndRegionDirectiveTrivia, startToken,
                                                                                              endRegionKeyword, endOfDirectiveToken, isActive);

    return static_cast<DelphiEndRegionDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrEndRegionDirectiveTrivia)));
}

} // end namespace polyglot::Delphi::Syntax
