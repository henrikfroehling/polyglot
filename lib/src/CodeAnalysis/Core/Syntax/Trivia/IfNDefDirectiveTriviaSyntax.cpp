#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/IfNDefDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

IfNDefDirectiveTriviaSyntax::IfNDefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                         SyntaxToken* startToken,
                                                         SyntaxToken* ifNDefKeyword,
                                                         SyntaxToken* name,
                                                         SyntaxToken* endOfDirectiveToken,
                                                         bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _ptrStartToken{startToken},
      _ptrIfNDefKeyword{ifNDefKeyword},
      _ptrName{name},
      _ptrEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _ptrStartToken->position();
}

IfNDefDirectiveTriviaSyntax* IfNDefDirectiveTriviaSyntax::create(SyntaxToken* startToken,
                                                                 SyntaxToken* ifNDefKeyword,
                                                                 SyntaxToken* name,
                                                                 SyntaxToken* endOfDirectiveToken,
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

    return static_cast<IfNDefDirectiveTriviaSyntax*>(SyntaxPool::addSyntaxTrivia(std::move(ptrIfNDefDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
