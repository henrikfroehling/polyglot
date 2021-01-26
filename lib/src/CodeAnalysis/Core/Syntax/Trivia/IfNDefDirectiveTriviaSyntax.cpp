#include "CodeAnalysis/Core/Syntax/Trivia/IfNDefDirectiveTriviaSyntax.hpp"
#include "CodeAnalysis/Core/Parser/SyntaxPool.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

IfNDefDirectiveTriviaSyntax::IfNDefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                         LanguageSyntaxToken* startToken,
                                                         LanguageSyntaxToken* ifNDefKeyword,
                                                         LanguageSyntaxToken* name,
                                                         LanguageSyntaxToken* endOfDirectiveToken,
                                                         bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pIfNDefKeyword{ifNDefKeyword},
      _pName{name},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _pStartToken->position();
}

IfNDefDirectiveTriviaSyntax* IfNDefDirectiveTriviaSyntax::create(LanguageSyntaxToken* startToken,
                                                                 LanguageSyntaxToken* ifNDefKeyword,
                                                                 LanguageSyntaxToken* name,
                                                                 LanguageSyntaxToken* endOfDirectiveToken,
                                                                 bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(ifNDefKeyword != nullptr);
    assert(ifNDefKeyword->syntaxKind() == SyntaxKind::IfNDefDirectiveKeyword);
    assert(name != nullptr);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrIfNDefDirectiveTrivia = std::make_unique<IfNDefDirectiveTriviaSyntax>(SyntaxKind::IfNDefDirectiveTrivia, startToken,
                                                                                  ifNDefKeyword, name, endOfDirectiveToken, isActive);

    return static_cast<IfNDefDirectiveTriviaSyntax*>(SyntaxPool::addSyntaxTrivia(std::move(ptrIfNDefDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
