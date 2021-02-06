#include "CodeAnalysis/Core/Syntax/Trivia/DefineDirectiveTriviaSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

DefineDirectiveTriviaSyntax::DefineDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                         LanguageSyntaxToken* startToken,
                                                         LanguageSyntaxToken* defineKeyword,
                                                         LanguageSyntaxToken* name,
                                                         LanguageSyntaxToken* endOfDirectiveToken,
                                                         bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pDefineKeyword{defineKeyword},
      _pName{name},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _pStartToken->position();
    adjustWidthAndFlags(_pStartToken);
    adjustWidthAndFlags(_pDefineKeyword);
    adjustWidthAndFlags(_pName);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
}

DefineDirectiveTriviaSyntax* DefineDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                                 LanguageSyntaxToken* startToken,
                                                                 LanguageSyntaxToken* defineKeyword,
                                                                 LanguageSyntaxToken* name,
                                                                 LanguageSyntaxToken* endOfDirectiveToken,
                                                                 bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(defineKeyword != nullptr);
    assert(defineKeyword->syntaxKind() == SyntaxKind::DefineDirectiveKeyword);
    assert(name != nullptr);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrDefineDirectiveTrivia = std::make_unique<DefineDirectiveTriviaSyntax>(SyntaxKind::DefineDirectiveTrivia, startToken,
                                                                                  defineKeyword, name, endOfDirectiveToken, isActive);

    return static_cast<DefineDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrDefineDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
