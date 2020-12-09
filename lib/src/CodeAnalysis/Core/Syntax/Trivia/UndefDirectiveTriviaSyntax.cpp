#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/UndefDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

UndefDirectiveTriviaSyntax::UndefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                       SyntaxToken* startToken,
                                                       SyntaxToken* undefKeyword,
                                                       SyntaxToken* name,
                                                       SyntaxToken* endOfDirectiveToken,
                                                       bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _ptrStartToken{startToken},
      _ptrUndefKeyword{undefKeyword},
      _ptrName{name},
      _ptrEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{}

UndefDirectiveTriviaSyntax* UndefDirectiveTriviaSyntax::create(SyntaxToken* startToken,
                                                               SyntaxToken* undefKeyword,
                                                               SyntaxToken* name,
                                                               SyntaxToken* endOfDirectiveToken,
                                                               bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(undefKeyword != nullptr);
    assert(undefKeyword->syntaxKind() == SyntaxKind::UndefDirectiveKeyword);
    assert(name != nullptr);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrUndefDirectiveTrivia = std::make_unique<UndefDirectiveTriviaSyntax>(SyntaxKind::UndefDirectiveTrivia, startToken,
                                                                                undefKeyword, name, endOfDirectiveToken, isActive);

    return static_cast<UndefDirectiveTriviaSyntax*>(SyntaxPool::addSyntaxTrivia(std::move(ptrUndefDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
