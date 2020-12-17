#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/BadDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

BadDirectiveTriviaSyntax::BadDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                   SyntaxToken* startToken,
                                                   SyntaxToken* identifier,
                                                   SyntaxToken* endOfDirectiveToken,
                                                   bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pIdentifier{identifier},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _pStartToken->position();
}

BadDirectiveTriviaSyntax* BadDirectiveTriviaSyntax::create(SyntaxToken* startToken,
                                                           SyntaxToken* identifier,
                                                           SyntaxToken* endOfDirectiveToken,
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
