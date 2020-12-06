#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DefineDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

DefineDirectiveTriviaSyntax::DefineDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                         Ptr<SyntaxToken> startToken,
                                                         Ptr<SyntaxToken> defineKeyword,
                                                         Ptr<SyntaxToken> name,
                                                         Ptr<SyntaxToken> endOfDirectiveToken,
                                                         bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _ptrStartToken{startToken},
      _ptrDefineKeyword{defineKeyword},
      _ptrName{name},
      _ptrEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{}

Ptr<DefineDirectiveTriviaSyntax> DefineDirectiveTriviaSyntax::create(Ptr<SyntaxToken> startToken,
                                                                     Ptr<SyntaxToken> defineKeyword,
                                                                     Ptr<SyntaxToken> name,
                                                                     Ptr<SyntaxToken> endOfDirectiveToken,
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
