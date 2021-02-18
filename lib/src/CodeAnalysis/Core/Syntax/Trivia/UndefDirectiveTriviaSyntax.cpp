#include "CodeAnalysis/Core/Syntax/Trivia/UndefDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include <cassert>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

UndefDirectiveTriviaSyntax::UndefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                       ISyntaxToken* startToken,
                                                       ISyntaxToken* undefKeyword,
                                                       ISyntaxToken* name,
                                                       ISyntaxToken* endOfDirectiveToken,
                                                       bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pUndefKeyword{undefKeyword},
      _pName{name},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _pStartToken->position();
}

ISyntaxNode* UndefDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pStartToken;
        case 1: return _pUndefKeyword;
        case 2: return _pName;
        case 3: return _pEndOfDirectiveToken;
    }

    throw std::out_of_range{"index out of range"};
}

UndefDirectiveTriviaSyntax* UndefDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
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

    auto ptrUndefDirectiveTrivia = std::make_unique<UndefDirectiveTriviaSyntax>(SyntaxKind::UndefDirectiveTrivia, startToken,
                                                                                undefKeyword, name, endOfDirectiveToken, isActive);

    return static_cast<UndefDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrUndefDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
