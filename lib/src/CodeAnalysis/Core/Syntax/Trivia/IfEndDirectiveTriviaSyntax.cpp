#include "CodeAnalysis/Core/Syntax/Trivia/IfEndDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

IfEndDirectiveTriviaSyntax::IfEndDirectiveTriviaSyntax(SyntaxKind syntaxKind,
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
    adjustWidthAndFlags(_pStartToken);
    _pStartToken->setChildNumber(0);
    adjustWidthAndFlags(_pIfEndKeyword);
    _pIfEndKeyword->setChildNumber(1);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
    _pEndOfDirectiveToken->setChildNumber(2);
}

ISyntaxNode* IfEndDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pStartToken;
        case 1: return _pIfEndKeyword;
        case 2: return _pEndOfDirectiveToken;
    }

    throw std::out_of_range{"index out of range"};
}

IfEndDirectiveTriviaSyntax* IfEndDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
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

    auto ptrIfEndDirectiveTrivia = std::make_unique<IfEndDirectiveTriviaSyntax>(SyntaxKind::IfEndDirectiveTrivia, startToken,
                                                                                ifEndKeyword, endOfDirectiveToken, isActive);

    return dynamic_cast<IfEndDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrIfEndDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
