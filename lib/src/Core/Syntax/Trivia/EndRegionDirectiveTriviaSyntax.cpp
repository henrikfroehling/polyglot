#include "EndRegionDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Core::Syntax
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
    adjustWidth(_pStartToken);
    adjustWidth(_pEndRegionKeyword);
    adjustWidth(_pEndOfDirectiveToken);
}

SyntaxNodeOrToken EndRegionDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxNodeOrToken::asToken(_pStartToken);
        case 1: return SyntaxNodeOrToken::asToken(_pEndRegionKeyword);
        case 2: return SyntaxNodeOrToken::asToken(_pEndOfDirectiveToken);
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

    return dynamic_cast<EndRegionDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrEndRegionDirectiveTrivia)));
}

} // end namespace polyglot::Core::Syntax
