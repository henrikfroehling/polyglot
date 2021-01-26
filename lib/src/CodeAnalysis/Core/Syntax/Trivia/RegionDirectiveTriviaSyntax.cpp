#include "CodeAnalysis/Core/Syntax/Trivia/RegionDirectiveTriviaSyntax.hpp"
#include "CodeAnalysis/Core/Parser/SyntaxPool.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

RegionDirectiveTriviaSyntax::RegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                         LanguageSyntaxToken* startToken,
                                                         LanguageSyntaxToken* regionKeyword,
                                                         LanguageSyntaxToken* endOfDirectiveToken,
                                                         bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pRegionKeyword{regionKeyword},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _pStartToken->position();
}

RegionDirectiveTriviaSyntax* RegionDirectiveTriviaSyntax::create(LanguageSyntaxToken* startToken,
                                                                 LanguageSyntaxToken* regionKeyword,
                                                                 LanguageSyntaxToken* endOfDirectiveToken,
                                                                 bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(regionKeyword != nullptr);
    assert(regionKeyword->syntaxKind() == SyntaxKind::RegionDirectiveKeyword);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrRegionDirectiveTrivia = std::make_unique<RegionDirectiveTriviaSyntax>(SyntaxKind::RegionDirectiveTrivia, startToken,
                                                                                  regionKeyword, endOfDirectiveToken, isActive);

    return static_cast<RegionDirectiveTriviaSyntax*>(SyntaxPool::addSyntaxTrivia(std::move(ptrRegionDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
