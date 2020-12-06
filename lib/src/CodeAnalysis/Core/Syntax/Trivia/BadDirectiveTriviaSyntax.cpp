#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/BadDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

BadDirectiveTriviaSyntax::BadDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                   Ptr<SyntaxToken> startToken,
                                                   Ptr<SyntaxToken> identifier,
                                                   Ptr<SyntaxToken> endOfDirectiveToken,
                                                   bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _ptrStartToken{startToken},
      _ptrIdentifier{identifier},
      _ptrEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{}

Ptr<BadDirectiveTriviaSyntax> BadDirectiveTriviaSyntax::create(Ptr<SyntaxToken> startToken,
                                                               Ptr<SyntaxToken> identifier,
                                                               Ptr<SyntaxToken> endOfDirectiveToken,
                                                               bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(identifier != nullptr);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrBadDirectiveTrivia = std::make_unique<BadDirectiveTriviaSyntax>(SyntaxKind::BadDirectiveTrivia, startToken,
                                                                            identifier, endOfDirectiveToken, isActive);

    return static_cast<BadDirectiveTriviaSyntax*>(SyntaxPool::addSyntaxTrivia(std::move(ptrBadDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
