#include "CodeAnalysis/Core/Syntax/Trivia/IfNDefDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

IfNDefDirectiveTriviaSyntax::IfNDefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
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
    adjustWidthAndFlags(_pStartToken);
    adjustWidthAndFlags(_pIfNDefKeyword);
    adjustWidthAndFlags(_pName);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
}

ISyntaxNode* IfNDefDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pStartToken;
        case 1: return _pIfNDefKeyword;
        case 2: return _pName;
        case 3: return _pEndOfDirectiveToken;
    }

    throw std::out_of_range{"index out of range"};
}

IfNDefDirectiveTriviaSyntax* IfNDefDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
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

    auto ptrIfNDefDirectiveTrivia = std::make_unique<IfNDefDirectiveTriviaSyntax>(SyntaxKind::IfNDefDirectiveTrivia, startToken,
                                                                                  ifNDefKeyword, name, endOfDirectiveToken, isActive);

    return static_cast<IfNDefDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrIfNDefDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
