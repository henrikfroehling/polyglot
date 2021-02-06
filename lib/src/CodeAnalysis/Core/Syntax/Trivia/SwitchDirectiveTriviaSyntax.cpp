#include "CodeAnalysis/Core/Syntax/Trivia/SwitchDirectiveTriviaSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

SwitchDirectiveTriviaSyntax::SwitchDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                         LanguageSyntaxToken* startToken,
                                                         LanguageSyntaxToken* identifier,
                                                         LanguageSyntaxToken* onOffToken,
                                                         LanguageSyntaxToken* endOfDirectiveToken) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pIdentifier{identifier},
      _pOnOffToken{onOffToken},
      _pEndOfDirectiveToken{endOfDirectiveToken}
{
    _position = _pStartToken->position();
    adjustWidthAndFlags(_pStartToken);
    adjustWidthAndFlags(_pIdentifier);
    adjustWidthAndFlags(_pOnOffToken);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
}

SwitchDirectiveTriviaSyntax* SwitchDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                                 LanguageSyntaxToken* startToken,
                                                                 LanguageSyntaxToken* identifier,
                                                                 LanguageSyntaxToken* onOffToken,
                                                                 LanguageSyntaxToken* endOfDirectiveToken) noexcept
{
    assert(startToken != nullptr);
    assert(identifier != nullptr);
    assert(identifier->syntaxKind() == SyntaxKind::IdentifierToken);
    assert(onOffToken != nullptr);
    assert(onOffToken->syntaxKind() == SyntaxKind::OnDirectiveKeyword || onOffToken->syntaxKind() == SyntaxKind::OffDirectiveKeyword);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrSwitchDirectiveTrivia = std::make_unique<SwitchDirectiveTriviaSyntax>(SyntaxKind::SwitchDirectiveTrivia, startToken,
                                                                                  identifier, onOffToken, endOfDirectiveToken);

    return static_cast<SwitchDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrSwitchDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
