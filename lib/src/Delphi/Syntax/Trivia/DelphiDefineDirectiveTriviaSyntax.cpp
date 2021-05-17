#include "Delphi/Syntax/Trivia/DelphiDefineDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Core/Syntax/SyntaxToken.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiDefineDirectiveTriviaSyntax::DelphiDefineDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                                     ISyntaxToken* startToken,
                                                                     ISyntaxToken* defineKeyword,
                                                                     ISyntaxToken* name,
                                                                     ISyntaxToken* endOfDirectiveToken,
                                                                     bool isActive) noexcept
    : DefineDirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pDefineKeyword{defineKeyword},
      _pName{name},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _pStartToken->position();

    adjustWidth(_pStartToken);
    adjustWidth(_pDefineKeyword);
    adjustWidth(_pName);
    adjustWidth(_pEndOfDirectiveToken);

    static_cast<SyntaxToken*>(_pStartToken)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pDefineKeyword)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pName)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pEndOfDirectiveToken)->setTriviaParent(this);
}

SyntaxVariant DelphiDefineDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pStartToken);
        case 1: return SyntaxVariant::asToken(_pDefineKeyword);
        case 2: return SyntaxVariant::asToken(_pName);
        case 3: return SyntaxVariant::asToken(_pEndOfDirectiveToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiDefineDirectiveTriviaSyntax* DelphiDefineDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                                             ISyntaxToken* startToken,
                                                                             ISyntaxToken* defineKeyword,
                                                                             ISyntaxToken* name,
                                                                             ISyntaxToken* endOfDirectiveToken,
                                                                             bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(defineKeyword != nullptr);
    assert(defineKeyword->syntaxKind() == SyntaxKind::DefineDirectiveKeyword);
    assert(name != nullptr);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrDefineDirectiveTrivia = std::make_unique<DelphiDefineDirectiveTriviaSyntax>(SyntaxKind::DefineDirectiveTrivia, startToken,
                                                                                        defineKeyword, name, endOfDirectiveToken, isActive);

    return static_cast<DelphiDefineDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrDefineDirectiveTrivia)));
}

} // end namespace polyglot::Delphi::Syntax
