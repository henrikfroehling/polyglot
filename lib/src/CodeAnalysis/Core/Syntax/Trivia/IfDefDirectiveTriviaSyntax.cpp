#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/IfDefDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

IfDefDirectiveTriviaSyntax::IfDefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                       SyntaxToken* startToken,
                                                       SyntaxToken* ifDefKeyword,
                                                       SyntaxToken* name,
                                                       SyntaxToken* endOfDirectiveToken,
                                                       bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _ptrStartToken{startToken},
      _ptrIfDefKeyword{ifDefKeyword},
      _ptrName{name},
      _ptrEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _ptrStartToken->position();
}

IfDefDirectiveTriviaSyntax* IfDefDirectiveTriviaSyntax::create(SyntaxToken* startToken,
                                                               SyntaxToken* ifDefKeyword,
                                                               SyntaxToken* name,
                                                               SyntaxToken* endOfDirectiveToken,
                                                               bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(ifDefKeyword != nullptr);
    assert(ifDefKeyword->syntaxKind() == SyntaxKind::IfDefDirectiveKeyword);
    assert(name != nullptr);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrIfDefDirectiveTrivia = std::make_unique<IfDefDirectiveTriviaSyntax>(SyntaxKind::IfDefDirectiveTrivia, startToken,
                                                                                ifDefKeyword, name, endOfDirectiveToken, isActive);

    return static_cast<IfDefDirectiveTriviaSyntax*>(SyntaxPool::addSyntaxTrivia(std::move(ptrIfDefDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
