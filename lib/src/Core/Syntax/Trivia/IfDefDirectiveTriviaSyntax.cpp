#include "IfDefDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Core::Syntax
{

IfDefDirectiveTriviaSyntax::IfDefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                       ISyntaxToken* startToken,
                                                       ISyntaxToken* ifDefKeyword,
                                                       ISyntaxToken* name,
                                                       ISyntaxToken* endOfDirectiveToken,
                                                       bool isActive,
                                                       bool isBranchTaken) noexcept
    : ConditionalDirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pIfDefKeyword{ifDefKeyword},
      _pName{name},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive},
      _isBranchTaken{isBranchTaken}
{
    _position = _pStartToken->position();
    adjustWidth(_pStartToken);
    adjustWidth(_pIfDefKeyword);
    adjustWidth(_pName);
    adjustWidth(_pEndOfDirectiveToken);
}

SyntaxNodeOrToken IfDefDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxNodeOrToken::asToken(_pStartToken);
        case 1: return SyntaxNodeOrToken::asToken(_pIfDefKeyword);
        case 2: return SyntaxNodeOrToken::asToken(_pName);
        case 3: return SyntaxNodeOrToken::asToken(_pEndOfDirectiveToken);
    }

    throw std::out_of_range{"index out of range"};
}

IfDefDirectiveTriviaSyntax* IfDefDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                               ISyntaxToken* startToken,
                                                               ISyntaxToken* ifDefKeyword,
                                                               ISyntaxToken* name,
                                                               ISyntaxToken* endOfDirectiveToken,
                                                               bool isActive,
                                                               bool isBranchTaken) noexcept
{
    assert(startToken != nullptr);
    assert(ifDefKeyword != nullptr);
    assert(ifDefKeyword->syntaxKind() == SyntaxKind::IfDefDirectiveKeyword);
    assert(name != nullptr);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrIfDefDirectiveTrivia = std::make_unique<IfDefDirectiveTriviaSyntax>(SyntaxKind::IfDefDirectiveTrivia, startToken,
                                                                                ifDefKeyword, name, endOfDirectiveToken,
                                                                                isActive, isBranchTaken);

    return dynamic_cast<IfDefDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrIfDefDirectiveTrivia)));
}

} // end namespace polyglot::Core::Syntax
