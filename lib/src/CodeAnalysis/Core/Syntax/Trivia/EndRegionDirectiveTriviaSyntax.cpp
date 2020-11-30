#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/EndRegionDirectiveTriviaSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

EndRegionDirectiveTriviaSyntax::EndRegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                               SharedPtr<SyntaxToken> startToken,
                                                               SharedPtr<SyntaxToken> endRegionKeyword,
                                                               SharedPtr<SyntaxToken> endOfDirectiveToken,
                                                               bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _ptrStartToken{std::move(startToken)},
      _ptrEndRegionKeyword{std::move(endRegionKeyword)},
      _ptrEndOfDirectiveToken{std::move(endOfDirectiveToken)},
      _isActive{isActive}
{}

SharedPtr<EndRegionDirectiveTriviaSyntax> EndRegionDirectiveTriviaSyntax::Create(SharedPtr<SyntaxToken> startToken,
                                                                                 SharedPtr<SyntaxToken> endRegionKeyword,
                                                                                 SharedPtr<SyntaxToken> endOfDirectiveToken,
                                                                                 bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(endRegionKeyword != nullptr);
    assert(endRegionKeyword->syntaxKind() == SyntaxKind::EndRegionDirectiveKeyword);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    return std::make_shared<EndRegionDirectiveTriviaSyntax>(SyntaxKind::EndRegionDirectiveTrivia, std::move(startToken),
                                                            std::move(endRegionKeyword), std::move(endOfDirectiveToken), isActive);
}

} // end namespace polyglot::CodeAnalysis
