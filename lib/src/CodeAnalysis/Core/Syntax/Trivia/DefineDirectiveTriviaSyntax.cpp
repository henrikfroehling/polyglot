#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DefineDirectiveTriviaSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

DefineDirectiveTriviaSyntax::DefineDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                         SyntaxTokenPtr startToken,
                                                         SyntaxTokenPtr defineKeyword,
                                                         SyntaxTokenPtr name,
                                                         SyntaxTokenPtr endOfDirectiveToken,
                                                         bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
    _ptrStartToken{std::move(startToken)},
    _ptrDefineKeyword{std::move(defineKeyword)},
    _ptrName{std::move(name)},
    _ptrEndOfDirectiveToken{std::move(endOfDirectiveToken)},
    _isActive{isActive}
{}

DefineDirectiveTriviaSyntaxPtr DefineDirectiveTriviaSyntax::Create(SyntaxTokenPtr startToken,
                                                                   SyntaxTokenPtr defineKeyword,
                                                                   SyntaxTokenPtr name,
                                                                   SyntaxTokenPtr endOfDirectiveToken,
                                                                   bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(defineKeyword != nullptr);
    assert(defineKeyword->syntaxKind() == SyntaxKind::DefineDirectiveKeyword);
    assert(name != nullptr);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    return std::make_shared<DefineDirectiveTriviaSyntax>(SyntaxKind::DefineDirectiveTrivia, std::move(startToken),
                                                         std::move(defineKeyword), std::move(name),
                                                         std::move(endOfDirectiveToken), isActive);
}

} // end namespace polyglot::CodeAnalysis
