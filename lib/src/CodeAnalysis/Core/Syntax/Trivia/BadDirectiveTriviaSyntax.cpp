#include "CodeAnalysis/Core/Syntax/Trivia/BadDirectiveTriviaSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

BadDirectiveTriviaSyntax::BadDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                   LanguageSyntaxToken* startToken,
                                                   LanguageSyntaxToken* identifier,
                                                   LanguageSyntaxToken* endOfDirectiveToken,
                                                   bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pIdentifier{identifier},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _pStartToken->position();
    adjustWidthAndFlags(_pStartToken);
    adjustWidthAndFlags(_pIdentifier);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
}

BadDirectiveTriviaSyntax* BadDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                           LanguageSyntaxToken* startToken,
                                                           LanguageSyntaxToken* identifier,
                                                           LanguageSyntaxToken* endOfDirectiveToken,
                                                           bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(identifier != nullptr);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrBadDirectiveTrivia = std::make_unique<BadDirectiveTriviaSyntax>(SyntaxKind::BadDirectiveTrivia, startToken,
                                                                            identifier, endOfDirectiveToken, isActive);

    return static_cast<BadDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrBadDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
