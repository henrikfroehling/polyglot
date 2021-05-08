#include "SwitchDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Core::Syntax
{

SwitchDirectiveTriviaSyntax::SwitchDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                         ISyntaxToken* startToken,
                                                         ISyntaxToken* identifier,
                                                         ISyntaxToken* onOffToken,
                                                         ISyntaxToken* endOfDirectiveToken) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pIdentifier{identifier},
      _pOnOffToken{onOffToken},
      _pEndOfDirectiveToken{endOfDirectiveToken}
{
    _position = _pStartToken->position();
    adjustWidthAndFlags(_pStartToken);
    _pStartToken->setChildNumber(0);
    adjustWidthAndFlags(_pIdentifier);
    _pIdentifier->setChildNumber(1);
    adjustWidthAndFlags(_pOnOffToken);
    _pOnOffToken->setChildNumber(2);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
    _pEndOfDirectiveToken->setChildNumber(3);
}

ISyntaxNode* SwitchDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pStartToken;
        case 1: return _pIdentifier;
        case 2: return _pOnOffToken;
        case 3: return _pEndOfDirectiveToken;
    }

    throw std::out_of_range{"index out of range"};
}

SwitchDirectiveTriviaSyntax* SwitchDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                                 ISyntaxToken* startToken,
                                                                 ISyntaxToken* identifier,
                                                                 ISyntaxToken* onOffToken,
                                                                 ISyntaxToken* endOfDirectiveToken) noexcept
{
    assert(startToken != nullptr);
    assert(identifier != nullptr);
    assert(identifier->syntaxKind() == SyntaxKind::IdentifierToken);
    assert(onOffToken != nullptr);
    assert(onOffToken->syntaxKind() == SyntaxKind::OnDirectiveKeyword || onOffToken->syntaxKind() == SyntaxKind::OffDirectiveKeyword);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrSwitchDirectiveTrivia = std::make_unique<SwitchDirectiveTriviaSyntax>(SyntaxKind::SwitchDirectiveTrivia, startToken,
                                                                                  identifier, onOffToken, endOfDirectiveToken);

    return dynamic_cast<SwitchDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrSwitchDirectiveTrivia)));
}

} // end namespace polyglot::Core::Syntax
