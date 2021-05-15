#include "Delphi/Syntax/Trivia/DelphiIfEndDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Core/Syntax/SyntaxToken.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiIfEndDirectiveTriviaSyntax::DelphiIfEndDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                                   ISyntaxToken* startToken,
                                                                   ISyntaxToken* ifEndKeyword,
                                                                   ISyntaxToken* endOfDirectiveToken,
                                                                   bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pIfEndKeyword{ifEndKeyword},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _pStartToken->position();

    adjustWidth(_pStartToken);
    adjustWidth(_pIfEndKeyword);
    adjustWidth(_pEndOfDirectiveToken);

    static_cast<SyntaxToken*>(_pStartToken)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pIfEndKeyword)->setTriviaParent(this);
    static_cast<SyntaxToken*>(_pEndOfDirectiveToken)->setTriviaParent(this);
}

SyntaxVariant DelphiIfEndDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pStartToken);
        case 1: return SyntaxVariant::asToken(_pIfEndKeyword);
        case 2: return SyntaxVariant::asToken(_pEndOfDirectiveToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiIfEndDirectiveTriviaSyntax* DelphiIfEndDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                                           ISyntaxToken* startToken,
                                                                           ISyntaxToken* ifEndKeyword,
                                                                           ISyntaxToken* endOfDirectiveToken,
                                                                           bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(ifEndKeyword != nullptr);
    assert(ifEndKeyword->syntaxKind() == SyntaxKind::IfEndDirectiveKeyword);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrIfEndDirectiveTrivia = std::make_unique<DelphiIfEndDirectiveTriviaSyntax>(SyntaxKind::IfEndDirectiveTrivia, startToken,
                                                                                      ifEndKeyword, endOfDirectiveToken, isActive);

    return dynamic_cast<DelphiIfEndDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrIfEndDirectiveTrivia)));
}

} // end namespace polyglot::Delphi::Syntax
