#include "CodeAnalysis/Core/Syntax/Trivia/DefineDirectiveTriviaSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
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
}

DefineDirectiveTriviaSyntax* DefineDirectiveTriviaSyntax::create(LanguageSyntaxToken* startToken,
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

    return static_cast<DefineDirectiveTriviaSyntax*>(SyntaxPool::addSyntaxTrivia(std::move(ptrDefineDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
