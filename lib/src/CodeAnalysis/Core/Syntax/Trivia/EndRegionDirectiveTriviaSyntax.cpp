#include "CodeAnalysis/Core/Syntax/Trivia/EndRegionDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

EndRegionDirectiveTriviaSyntax::EndRegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
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
    adjustWidthAndFlags(_pStartToken);
    adjustWidthAndFlags(_pEndRegionKeyword);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
}

ISyntaxNode* EndRegionDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pStartToken;
        case 1: return _pEndRegionKeyword;
        case 2: return _pEndOfDirectiveToken;
    }

    throw std::out_of_range{"index out of range"};
}

EndRegionDirectiveTriviaSyntax* EndRegionDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
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

    auto ptrEndRegionDirectiveTrivia = std::make_unique<EndRegionDirectiveTriviaSyntax>(SyntaxKind::EndRegionDirectiveTrivia, startToken,
                                                                                        endRegionKeyword, endOfDirectiveToken, isActive);

    return static_cast<EndRegionDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrEndRegionDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
