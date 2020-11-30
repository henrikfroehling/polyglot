#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/BadDirectiveTriviaSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

BadDirectiveTriviaSyntax::BadDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                   SharedPtr<SyntaxToken> startToken,
                                                   SharedPtr<SyntaxToken> identifier,
                                                   SharedPtr<SyntaxToken> endOfDirectiveToken,
                                                   bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _ptrStartToken{std::move(startToken)},
      _ptrIdentifier{std::move(identifier)},
      _ptrEndOfDirectiveToken{std::move(endOfDirectiveToken)},
      _isActive{isActive}
{}

SharedPtr<BadDirectiveTriviaSyntax> BadDirectiveTriviaSyntax::create(SharedPtr<SyntaxToken> startToken,
                                                                     SharedPtr<SyntaxToken> identifier,
                                                                     SharedPtr<SyntaxToken> endOfDirectiveToken,
                                                                     bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(identifier != nullptr);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    return std::make_shared<BadDirectiveTriviaSyntax>(SyntaxKind::BadDirectiveTrivia, std::move(startToken),
                                                      std::move(identifier), std::move(endOfDirectiveToken), isActive);
}

} // end namespace polyglot::CodeAnalysis
