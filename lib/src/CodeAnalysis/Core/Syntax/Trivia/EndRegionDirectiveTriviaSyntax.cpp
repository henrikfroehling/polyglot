#include "CodeAnalysis/Core/Syntax/Trivia/EndRegionDirectiveTriviaSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

EndRegionDirectiveTriviaSyntax::EndRegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                               SyntaxToken* startToken,
                                                               SyntaxToken* endRegionKeyword,
                                                               SyntaxToken* endOfDirectiveToken,
                                                               bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pEndRegionKeyword{endRegionKeyword},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _pStartToken->position();
}

EndRegionDirectiveTriviaSyntax* EndRegionDirectiveTriviaSyntax::create(SyntaxToken* startToken,
                                                                       SyntaxToken* endRegionKeyword,
                                                                       SyntaxToken* endOfDirectiveToken,
                                                                       bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(endRegionKeyword != nullptr);
    assert(endRegionKeyword->syntaxKind() == SyntaxKind::EndRegionDirectiveKeyword);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrEndRegionDirectiveTrivia = std::make_unique<EndRegionDirectiveTriviaSyntax>(SyntaxKind::EndRegionDirectiveTrivia, startToken,
                                                                                        endRegionKeyword, endOfDirectiveToken, isActive);

    return static_cast<EndRegionDirectiveTriviaSyntax*>(SyntaxPool::addSyntaxTrivia(std::move(ptrEndRegionDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
