#include "Delphi/Syntax/Trivia/DelphiSwitchDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Core/Syntax/SyntaxToken.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiSwitchDirectiveTriviaSyntax::DelphiSwitchDirectiveTriviaSyntax(SyntaxKind syntaxKind,
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

    adjustWidth(_pStartToken);
    adjustWidth(_pIdentifier);
    adjustWidth(_pOnOffToken);
    adjustWidth(_pEndOfDirectiveToken);

    static_cast<SyntaxToken*>(_pStartToken)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pIdentifier)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pOnOffToken)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pEndOfDirectiveToken)->setTriviaParent(this);
}

SyntaxVariant DelphiSwitchDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pStartToken);
        case 1: return SyntaxVariant::asToken(_pIdentifier);
        case 2: return SyntaxVariant::asToken(_pOnOffToken);
        case 3: return SyntaxVariant::asToken(_pEndOfDirectiveToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiSwitchDirectiveTriviaSyntax* DelphiSwitchDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
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

    auto ptrSwitchDirectiveTrivia = std::make_unique<DelphiSwitchDirectiveTriviaSyntax>(SyntaxKind::SwitchDirectiveTrivia, startToken,
                                                                                        identifier, onOffToken, endOfDirectiveToken);

    return static_cast<DelphiSwitchDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrSwitchDirectiveTrivia)));
}

} // end namespace polyglot::Delphi::Syntax
