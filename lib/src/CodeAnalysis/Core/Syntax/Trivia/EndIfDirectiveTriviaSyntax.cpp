#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/EndIfDirectiveTriviaSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

EndIfDirectiveTriviaSyntax::EndIfDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                       SharedPtr<SyntaxToken> startToken,
                                                       SharedPtr<SyntaxToken> endIfKeyword,
                                                       SharedPtr<SyntaxToken> endOfDirectiveToken,
                                                       bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _ptrStartToken{std::move(startToken)},
      _ptrEndIfKeyword{std::move(endIfKeyword)},
      _ptrEndOfDirectiveToken{std::move(endOfDirectiveToken)},
      _isActive{isActive}
{}

SharedPtr<EndIfDirectiveTriviaSyntax> EndIfDirectiveTriviaSyntax::create(SharedPtr<SyntaxToken> startToken,
                                                                         SharedPtr<SyntaxToken> endIfKeyword,
                                                                         SharedPtr<SyntaxToken> endOfDirectiveToken,
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
