#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/EndIfDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

EndIfDirectiveTriviaSyntax::EndIfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                       Ptr<SyntaxToken> startToken,
                                                       Ptr<SyntaxToken> endIfKeyword,
                                                       Ptr<SyntaxToken> endOfDirectiveToken,
                                                       bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _ptrStartToken{startToken},
      _ptrEndIfKeyword{endIfKeyword},
      _ptrEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{}

Ptr<EndIfDirectiveTriviaSyntax> EndIfDirectiveTriviaSyntax::create(Ptr<SyntaxToken> startToken,
                                                                   Ptr<SyntaxToken> endIfKeyword,
                                                                   Ptr<SyntaxToken> endOfDirectiveToken,
                                                                   bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(endIfKeyword != nullptr);
    assert(endIfKeyword->syntaxKind() == SyntaxKind::EndIfDirectiveKeyword);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrEndIfDirectiveTrivia = std::make_unique<EndIfDirectiveTriviaSyntax>(SyntaxKind::EndIfDirectiveTrivia, startToken,
                                                                                endIfKeyword, endOfDirectiveToken, isActive);

    return static_cast<EndIfDirectiveTriviaSyntax*>(SyntaxPool::addSyntaxTrivia(std::move(ptrEndIfDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
