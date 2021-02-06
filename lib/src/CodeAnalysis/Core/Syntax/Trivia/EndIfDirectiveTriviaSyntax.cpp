#include "CodeAnalysis/Core/Syntax/Trivia/EndIfDirectiveTriviaSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

EndIfDirectiveTriviaSyntax::EndIfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                       LanguageSyntaxToken* startToken,
                                                       LanguageSyntaxToken* endIfKeyword,
                                                       LanguageSyntaxToken* endOfDirectiveToken,
                                                       bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pEndIfKeyword{endIfKeyword},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _pStartToken->position();
    adjustWidthAndFlags(_pStartToken);
    adjustWidthAndFlags(_pEndIfKeyword);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
}

EndIfDirectiveTriviaSyntax* EndIfDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                               LanguageSyntaxToken* startToken,
                                                               LanguageSyntaxToken* endIfKeyword,
                                                               LanguageSyntaxToken* endOfDirectiveToken,
                                                               bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(endIfKeyword != nullptr);
    assert(endIfKeyword->syntaxKind() == SyntaxKind::EndIfDirectiveKeyword);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrEndIfDirectiveTrivia = std::make_unique<EndIfDirectiveTriviaSyntax>(SyntaxKind::EndIfDirectiveTrivia, startToken,
                                                                                endIfKeyword, endOfDirectiveToken, isActive);

    return static_cast<EndIfDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrEndIfDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
