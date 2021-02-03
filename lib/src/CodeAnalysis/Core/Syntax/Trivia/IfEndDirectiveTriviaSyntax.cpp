#include "CodeAnalysis/Core/Syntax/Trivia/IfEndDirectiveTriviaSyntax.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxPool.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

IfEndDirectiveTriviaSyntax::IfEndDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                       LanguageSyntaxToken* startToken,
                                                       LanguageSyntaxToken* ifEndKeyword,
                                                       LanguageSyntaxToken* endOfDirectiveToken,
                                                       bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pIfEndKeyword{ifEndKeyword},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _pStartToken->position();
    adjustWidthAndFlags(_pStartToken);
    adjustWidthAndFlags(_pIfEndKeyword);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
}

IfEndDirectiveTriviaSyntax* IfEndDirectiveTriviaSyntax::create(LanguageSyntaxToken* startToken,
                                                               LanguageSyntaxToken* ifEndKeyword,
                                                               LanguageSyntaxToken* endOfDirectiveToken,
                                                               bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(ifEndKeyword != nullptr);
    assert(ifEndKeyword->syntaxKind() == SyntaxKind::IfEndDirectiveKeyword);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrIfEndDirectiveTrivia = std::make_unique<IfEndDirectiveTriviaSyntax>(SyntaxKind::IfEndDirectiveTrivia, startToken,
                                                                                ifEndKeyword, endOfDirectiveToken, isActive);

    return static_cast<IfEndDirectiveTriviaSyntax*>(SyntaxPool::addSyntaxTrivia(std::move(ptrIfEndDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
