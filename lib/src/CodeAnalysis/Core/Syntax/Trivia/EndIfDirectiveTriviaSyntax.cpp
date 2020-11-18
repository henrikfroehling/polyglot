#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/EndIfDirectiveTriviaSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

EndIfDirectiveTriviaSyntax::EndIfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                       SyntaxTokenPtr startToken,
                                                       SyntaxTokenPtr endIfKeyword,
                                                       SyntaxTokenPtr endOfDirectiveToken,
                                                       bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
    _ptrStartToken{std::move(startToken)},
    _ptrEndIfKeyword{std::move(endIfKeyword)},
    _ptrEndOfDirectiveToken{std::move(endOfDirectiveToken)},
    _isActive{isActive}
{}

EndIfDirectiveTriviaSyntaxPtr EndIfDirectiveTriviaSyntax::create(SyntaxTokenPtr startToken,
                                                                 SyntaxTokenPtr endIfKeyword,
                                                                 SyntaxTokenPtr endOfDirectiveToken,
                                                                 bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(endIfKeyword != nullptr);
    assert(endIfKeyword->syntaxKind() == SyntaxKind::EndIfDirectiveKeyword);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    return std::make_shared<EndIfDirectiveTriviaSyntax>(SyntaxKind::EndIfDirectiveTrivia, std::move(startToken),
                                                        std::move(endIfKeyword), std::move(endOfDirectiveToken), isActive);
}

} // end namespace polyglot::CodeAnalysis
