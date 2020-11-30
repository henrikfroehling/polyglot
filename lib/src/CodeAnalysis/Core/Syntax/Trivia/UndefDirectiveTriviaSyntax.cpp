#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/UndefDirectiveTriviaSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

UndefDirectiveTriviaSyntax::UndefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                       SharedPtr<SyntaxToken> startToken,
                                                       SharedPtr<SyntaxToken> undefKeyword,
                                                       SharedPtr<SyntaxToken> name,
                                                       SharedPtr<SyntaxToken> endOfDirectiveToken,
                                                       bool isActive) noexcept
    : DirectiveTriviaSyntax{ syntaxKind },
      _ptrStartToken{ std::move(startToken) },
      _ptrUndefKeyword{ std::move(undefKeyword) },
      _ptrName{ std::move(name) },
      _ptrEndOfDirectiveToken{ std::move(endOfDirectiveToken) },
      _isActive{ isActive }
{}

SharedPtr<UndefDirectiveTriviaSyntax> UndefDirectiveTriviaSyntax::create(SharedPtr<SyntaxToken> startToken,
                                                                         SharedPtr<SyntaxToken> undefKeyword,
                                                                         SharedPtr<SyntaxToken> name,
                                                                         SharedPtr<SyntaxToken> endOfDirectiveToken,
                                                                         bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(undefKeyword != nullptr);
    assert(undefKeyword->syntaxKind() == SyntaxKind::UndefDirectiveKeyword);
    assert(name != nullptr);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    return std::make_shared<UndefDirectiveTriviaSyntax>(SyntaxKind::UndefDirectiveTrivia, std::move(startToken),
                                                        std::move(undefKeyword), std::move(name),
                                                        std::move(endOfDirectiveToken), isActive);
}

} // end namespace polyglot::CodeAnalysis
