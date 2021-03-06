#include "Delphi/Syntax/Trivia/DelphiUndefDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Core/Syntax/SyntaxToken.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiUndefDirectiveTriviaSyntax::DelphiUndefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                                   ISyntaxToken* startToken,
                                                                   ISyntaxToken* undefKeyword,
                                                                   ISyntaxToken* name,
                                                                   ISyntaxToken* endOfDirectiveToken,
                                                                   bool isActive) noexcept
    : UndefDirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pUndefKeyword{undefKeyword},
      _pName{name},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _pStartToken->position();

    adjustWidth(_pStartToken);
    adjustWidth(_pUndefKeyword);
    adjustWidth(_pName);
    adjustWidth(_pEndOfDirectiveToken);

    static_cast<SyntaxToken*>(_pStartToken)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pUndefKeyword)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pName)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pEndOfDirectiveToken)->setTriviaParent(this);
}

SyntaxVariant DelphiUndefDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pStartToken);
        case 1: return SyntaxVariant::asToken(_pUndefKeyword);
        case 2: return SyntaxVariant::asToken(_pName);
        case 3: return SyntaxVariant::asToken(_pEndOfDirectiveToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiUndefDirectiveTriviaSyntax* DelphiUndefDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                                           ISyntaxToken* startToken,
                                                                           ISyntaxToken* undefKeyword,
                                                                           ISyntaxToken* name,
                                                                           ISyntaxToken* endOfDirectiveToken,
                                                                           bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(undefKeyword != nullptr);
    assert(undefKeyword->syntaxKind() == SyntaxKind::UndefDirectiveKeyword);
    assert(name != nullptr);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrUndefDirectiveTrivia = std::make_unique<DelphiUndefDirectiveTriviaSyntax>(SyntaxKind::UndefDirectiveTrivia, startToken,
                                                                                      undefKeyword, name, endOfDirectiveToken, isActive);

    return static_cast<DelphiUndefDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrUndefDirectiveTrivia)));
}

} // end namespace polyglot::Delphi::Syntax
