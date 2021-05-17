#include "Delphi/Syntax/Trivia/DelphiBadDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Core/Syntax/SyntaxToken.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiBadDirectiveTriviaSyntax::DelphiBadDirectiveTriviaSyntax(SyntaxKind syntaxKind,
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

    adjustWidth(_pStartToken);
    adjustWidth(_pIdentifier);
    adjustWidth(_pEndOfDirectiveToken);

    static_cast<SyntaxToken*>(_pStartToken)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pIdentifier)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pEndOfDirectiveToken)->setTriviaParent(this);
}

SyntaxVariant DelphiBadDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pStartToken);
        case 1: return SyntaxVariant::asToken(_pIdentifier);
        case 2: return SyntaxVariant::asToken(_pEndOfDirectiveToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiBadDirectiveTriviaSyntax* DelphiBadDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                                       ISyntaxToken* startToken,
                                                                       ISyntaxToken* identifier,
                                                                       ISyntaxToken* endOfDirectiveToken,
                                                                       bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(identifier != nullptr);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrBadDirectiveTrivia = std::make_unique<DelphiBadDirectiveTriviaSyntax>(SyntaxKind::BadDirectiveTrivia, startToken,
                                                                                  identifier, endOfDirectiveToken, isActive);

    return static_cast<DelphiBadDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrBadDirectiveTrivia)));
}

} // end namespace polyglot::Delphi::Syntax
