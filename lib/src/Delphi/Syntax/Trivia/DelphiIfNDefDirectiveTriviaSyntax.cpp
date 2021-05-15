#include "Delphi/Syntax/Trivia/DelphiIfNDefDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Core/Syntax/SyntaxToken.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiIfNDefDirectiveTriviaSyntax::DelphiIfNDefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                                     ISyntaxToken* startToken,
                                                                     ISyntaxToken* ifNDefKeyword,
                                                                     ISyntaxToken* name,
                                                                     ISyntaxToken* endOfDirectiveToken,
                                                                     bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pIfNDefKeyword{ifNDefKeyword},
      _pName{name},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _pStartToken->position();

    adjustWidth(_pStartToken);
    adjustWidth(_pIfNDefKeyword);
    adjustWidth(_pName);
    adjustWidth(_pEndOfDirectiveToken);

    static_cast<SyntaxToken*>(_pStartToken)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pIfNDefKeyword)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pName)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pEndOfDirectiveToken)->setTriviaParent(this);
}

SyntaxVariant DelphiIfNDefDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pStartToken);
        case 1: return SyntaxVariant::asToken(_pIfNDefKeyword);
        case 2: return SyntaxVariant::asToken(_pName);
        case 3: return SyntaxVariant::asToken(_pEndOfDirectiveToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiIfNDefDirectiveTriviaSyntax* DelphiIfNDefDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                                             ISyntaxToken* startToken,
                                                                             ISyntaxToken* ifNDefKeyword,
                                                                             ISyntaxToken* name,
                                                                             ISyntaxToken* endOfDirectiveToken,
                                                                             bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(ifNDefKeyword != nullptr);
    assert(ifNDefKeyword->syntaxKind() == SyntaxKind::IfNDefDirectiveKeyword);
    assert(name != nullptr);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrIfNDefDirectiveTrivia = std::make_unique<DelphiIfNDefDirectiveTriviaSyntax>(SyntaxKind::IfNDefDirectiveTrivia, startToken,
                                                                                        ifNDefKeyword, name, endOfDirectiveToken, isActive);

    return dynamic_cast<DelphiIfNDefDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrIfNDefDirectiveTrivia)));
}

} // end namespace polyglot::Delphi::Syntax
