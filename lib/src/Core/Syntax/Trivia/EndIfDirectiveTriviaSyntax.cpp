#include "EndIfDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Core::Syntax
{

EndIfDirectiveTriviaSyntax::EndIfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                       ISyntaxToken* startToken,
                                                       ISyntaxToken* endIfKeyword,
                                                       ISyntaxToken* endOfDirectiveToken,
                                                       bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pEndIfKeyword{endIfKeyword},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _pStartToken->position();
    adjustWidth(_pStartToken);
    adjustWidth(_pEndIfKeyword);
    adjustWidth(_pEndOfDirectiveToken);
}

SyntaxVariant EndIfDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pStartToken);
        case 1: return SyntaxVariant::asToken(_pEndIfKeyword);
        case 2: return SyntaxVariant::asToken(_pEndOfDirectiveToken);
    }

    throw std::out_of_range{"index out of range"};
}

EndIfDirectiveTriviaSyntax* EndIfDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                               ISyntaxToken* startToken,
                                                               ISyntaxToken* endIfKeyword,
                                                               ISyntaxToken* endOfDirectiveToken,
                                                               bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(endIfKeyword != nullptr);
    assert(endIfKeyword->syntaxKind() == SyntaxKind::EndIfDirectiveKeyword);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrEndIfDirectiveTrivia = std::make_unique<EndIfDirectiveTriviaSyntax>(SyntaxKind::EndIfDirectiveTrivia, startToken,
                                                                                endIfKeyword, endOfDirectiveToken, isActive);

    return dynamic_cast<EndIfDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrEndIfDirectiveTrivia)));
}

} // end namespace polyglot::Core::Syntax
