#include "CodeAnalysis/Core/Syntax/Trivia/ElseDirectiveTriviaSyntax.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxPool.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

ElseDirectiveTriviaSyntax::ElseDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                     LanguageSyntaxToken* startToken,
                                                     LanguageSyntaxToken* elseKeyword,
                                                     LanguageSyntaxToken* endOfDirectiveToken,
                                                     bool isActive,
                                                     bool isBranchTaken) noexcept
    : BranchingDirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pElseKeyword{elseKeyword},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive},
      _isBranchTaken{isBranchTaken}
{
    _position = _pStartToken->position();
    adjustWidthAndFlags(_pStartToken);
    adjustWidthAndFlags(_pElseKeyword);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
}

ElseDirectiveTriviaSyntax* ElseDirectiveTriviaSyntax::create(LanguageSyntaxToken* startToken,
                                                             LanguageSyntaxToken* elseKeyword,
                                                             LanguageSyntaxToken* endOfDirectiveToken,
                                                             bool isActive,
                                                             bool isBranchTaken) noexcept
{
    assert(startToken != nullptr);
    assert(elseKeyword != nullptr);
    assert(elseKeyword->syntaxKind() == SyntaxKind::ElseDirectiveKeyword);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrElseDirectiveTrivia = std::make_unique<ElseDirectiveTriviaSyntax>(SyntaxKind::ElseDirectiveTrivia, startToken,
                                                                              elseKeyword, endOfDirectiveToken,
                                                                              isActive, isBranchTaken);

    return static_cast<ElseDirectiveTriviaSyntax*>(SyntaxPool::addSyntaxTrivia(std::move(ptrElseDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
