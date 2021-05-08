#include "BadDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Core::Syntax
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
    _pStartToken->setChildNumber(0);
    adjustWidthAndFlags(_pIdentifier);
    _pIdentifier->setChildNumber(1);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
    _pEndOfDirectiveToken->setChildNumber(2);
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

    return dynamic_cast<BadDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrBadDirectiveTrivia)));
}

} // end namespace polyglot::Core::Syntax
