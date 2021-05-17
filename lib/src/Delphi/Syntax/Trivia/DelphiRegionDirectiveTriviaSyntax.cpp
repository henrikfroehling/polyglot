#include "Delphi/Syntax/Trivia/DelphiRegionDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Core/Syntax/SyntaxToken.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiRegionDirectiveTriviaSyntax::DelphiRegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
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

    adjustWidth(_pStartToken);
    adjustWidth(_pRegionKeyword);
    adjustWidth(_pEndOfDirectiveToken);

    static_cast<SyntaxToken*>(_pStartToken)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pRegionKeyword)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pEndOfDirectiveToken)->setTriviaParent(this);
}

SyntaxVariant DelphiRegionDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pStartToken);
        case 1: return SyntaxVariant::asToken(_pRegionKeyword);
        case 2: return SyntaxVariant::asToken(_pEndOfDirectiveToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiRegionDirectiveTriviaSyntax* DelphiRegionDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
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

    auto ptrRegionDirectiveTrivia = std::make_unique<DelphiRegionDirectiveTriviaSyntax>(SyntaxKind::RegionDirectiveTrivia, startToken,
                                                                                        regionKeyword, endOfDirectiveToken, isActive);

    return static_cast<DelphiRegionDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrRegionDirectiveTrivia)));
}

} // end namespace polyglot::Delphi::Syntax
