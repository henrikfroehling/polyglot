#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/EndRegionDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

EndRegionDirectiveTriviaSyntax::EndRegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                               SyntaxToken* startToken,
                                                               SyntaxToken* endRegionKeyword,
                                                               SyntaxToken* endOfDirectiveToken,
                                                               bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _ptrStartToken{startToken},
      _ptrEndRegionKeyword{endRegionKeyword},
      _ptrEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{}

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
