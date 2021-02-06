#include "CodeAnalysis/Core/Syntax/Trivia/IfDefDirectiveTriviaSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

IfDefDirectiveTriviaSyntax::IfDefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                       LanguageSyntaxToken* startToken,
                                                       LanguageSyntaxToken* ifDefKeyword,
                                                       LanguageSyntaxToken* name,
                                                       LanguageSyntaxToken* endOfDirectiveToken,
                                                       bool isActive,
                                                       bool isBranchTaken) noexcept
    : ConditionalDirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pIfDefKeyword{ifDefKeyword},
      _pName{name},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive},
      _isBranchTaken{isBranchTaken}
{
    _position = _pStartToken->position();
    adjustWidthAndFlags(_pStartToken);
    adjustWidthAndFlags(_pIfDefKeyword);
    adjustWidthAndFlags(_pName);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
}

IfDefDirectiveTriviaSyntax* IfDefDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                               LanguageSyntaxToken* startToken,
                                                               LanguageSyntaxToken* ifDefKeyword,
                                                               LanguageSyntaxToken* name,
                                                               LanguageSyntaxToken* endOfDirectiveToken,
                                                               bool isActive,
                                                               bool isBranchTaken) noexcept
{
    assert(startToken != nullptr);
    assert(ifDefKeyword != nullptr);
    assert(ifDefKeyword->syntaxKind() == SyntaxKind::IfDefDirectiveKeyword);
    assert(name != nullptr);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrIfDefDirectiveTrivia = std::make_unique<IfDefDirectiveTriviaSyntax>(SyntaxKind::IfDefDirectiveTrivia, startToken,
                                                                                ifDefKeyword, name, endOfDirectiveToken,
                                                                                isActive, isBranchTaken);

    return static_cast<IfDefDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrIfDefDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
