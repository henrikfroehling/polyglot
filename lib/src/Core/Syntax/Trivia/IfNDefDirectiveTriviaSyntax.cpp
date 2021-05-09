#include "IfNDefDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Core::Syntax
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
    adjustWidth(_pStartToken);
    adjustWidth(_pIfNDefKeyword);
    adjustWidth(_pName);
    adjustWidth(_pEndOfDirectiveToken);
}

SyntaxNodeOrToken IfNDefDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxNodeOrToken::asToken(_pStartToken);
        case 1: return SyntaxNodeOrToken::asToken(_pIfNDefKeyword);
        case 2: return SyntaxNodeOrToken::asToken(_pName);
        case 3: return SyntaxNodeOrToken::asToken(_pEndOfDirectiveToken);
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

    return dynamic_cast<IfNDefDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrIfNDefDirectiveTrivia)));
}

} // end namespace polyglot::Core::Syntax
