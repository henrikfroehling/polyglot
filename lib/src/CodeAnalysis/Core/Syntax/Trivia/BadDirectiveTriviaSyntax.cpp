#include "CodeAnalysis/Core/Syntax/Trivia/BadDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

BadDirectiveTriviaSyntax::BadDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                   ISyntaxToken* startToken,
                                                   ISyntaxToken* identifier,
                                                   ISyntaxToken* endOfDirectiveToken,
                                                   bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pIdentifier{identifier},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _pStartToken->position();
    adjustWidthAndFlags(_pStartToken);
    adjustWidthAndFlags(_pIdentifier);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
}

ISyntaxNode* BadDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pStartToken;
        case 1: return _pIdentifier;
        case 2: return _pEndOfDirectiveToken;
    }

    throw std::out_of_range{"index out of range"};
}

BadDirectiveTriviaSyntax* BadDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                           ISyntaxToken* startToken,
                                                           ISyntaxToken* identifier,
                                                           ISyntaxToken* endOfDirectiveToken,
                                                           bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(identifier != nullptr);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrBadDirectiveTrivia = std::make_unique<BadDirectiveTriviaSyntax>(SyntaxKind::BadDirectiveTrivia, startToken,
                                                                            identifier, endOfDirectiveToken, isActive);

    return static_cast<BadDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrBadDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
