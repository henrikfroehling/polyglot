#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/RegionDirectiveTriviaSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

RegionDirectiveTriviaSyntax::RegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                         SharedPtr<SyntaxToken> startToken,
                                                         SharedPtr<SyntaxToken> regionKeyword,
                                                         SharedPtr<SyntaxToken> endOfDirectiveToken,
                                                         bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _ptrStartToken{std::move(startToken)},
      _ptrRegionKeyword{std::move(regionKeyword)},
      _ptrEndOfDirectiveToken{std::move(endOfDirectiveToken)},
      _isActive{isActive}
{}

SharedPtr<RegionDirectiveTriviaSyntax> RegionDirectiveTriviaSyntax::create(SharedPtr<SyntaxToken> startToken,
                                                                           SharedPtr<SyntaxToken> regionKeyword,
                                                                           SharedPtr<SyntaxToken> endOfDirectiveToken,
                                                                           bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(regionKeyword != nullptr);
    assert(regionKeyword->syntaxKind() == SyntaxKind::RegionDirectiveKeyword);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    return std::make_shared<RegionDirectiveTriviaSyntax>(SyntaxKind::RegionDirectiveTrivia, std::move(startToken),
                                                         std::move(regionKeyword), std::move(endOfDirectiveToken), isActive);
}

} // end namespace polyglot::CodeAnalysis
