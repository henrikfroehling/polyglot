#include "CodeAnalysis/Core/Syntax/Trivia/EndRegionDirectiveTriviaSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

EndRegionDirectiveTriviaSyntax::EndRegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                               LanguageSyntaxToken* startToken,
                                                               LanguageSyntaxToken* endRegionKeyword,
                                                               LanguageSyntaxToken* endOfDirectiveToken,
                                                               bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pEndRegionKeyword{endRegionKeyword},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _pStartToken->position();
    adjustWidthAndFlags(_pStartToken);
    adjustWidthAndFlags(_pEndRegionKeyword);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
}

EndRegionDirectiveTriviaSyntax* EndRegionDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                                       LanguageSyntaxToken* startToken,
                                                                       LanguageSyntaxToken* endRegionKeyword,
                                                                       LanguageSyntaxToken* endOfDirectiveToken,
                                                                       bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(endRegionKeyword != nullptr);
    assert(endRegionKeyword->syntaxKind() == SyntaxKind::EndRegionDirectiveKeyword);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrEndRegionDirectiveTrivia = std::make_unique<EndRegionDirectiveTriviaSyntax>(SyntaxKind::EndRegionDirectiveTrivia, startToken,
                                                                                        endRegionKeyword, endOfDirectiveToken, isActive);

    return static_cast<EndRegionDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrEndRegionDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
