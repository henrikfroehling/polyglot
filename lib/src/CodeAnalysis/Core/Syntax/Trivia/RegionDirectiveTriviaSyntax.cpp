#include "CodeAnalysis/Core/Syntax/Trivia/RegionDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

RegionDirectiveTriviaSyntax::RegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                         ISyntaxToken* startToken,
                                                         ISyntaxToken* regionKeyword,
                                                         ISyntaxToken* endOfDirectiveToken,
                                                         bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pRegionKeyword{regionKeyword},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _pStartToken->position();
    adjustWidthAndFlags(_pStartToken);
    adjustWidthAndFlags(_pRegionKeyword);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
}

ISyntaxNode* RegionDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pStartToken;
        case 1: return _pRegionKeyword;
        case 2: return _pEndOfDirectiveToken;
    }

    throw std::out_of_range{"index out of range"};
}

RegionDirectiveTriviaSyntax* RegionDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                                 ISyntaxToken* startToken,
                                                                 ISyntaxToken* regionKeyword,
                                                                 ISyntaxToken* endOfDirectiveToken,
                                                                 bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(regionKeyword != nullptr);
    assert(regionKeyword->syntaxKind() == SyntaxKind::RegionDirectiveKeyword);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrRegionDirectiveTrivia = std::make_unique<RegionDirectiveTriviaSyntax>(SyntaxKind::RegionDirectiveTrivia, startToken,
                                                                                  regionKeyword, endOfDirectiveToken, isActive);

    return static_cast<RegionDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrRegionDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
