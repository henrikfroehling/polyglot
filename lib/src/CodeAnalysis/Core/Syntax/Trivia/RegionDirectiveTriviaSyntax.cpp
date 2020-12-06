#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/RegionDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

RegionDirectiveTriviaSyntax::RegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                         Ptr<SyntaxToken> startToken,
                                                         Ptr<SyntaxToken> regionKeyword,
                                                         Ptr<SyntaxToken> endOfDirectiveToken,
                                                         bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _ptrStartToken{startToken},
      _ptrRegionKeyword{regionKeyword},
      _ptrEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{}

Ptr<RegionDirectiveTriviaSyntax> RegionDirectiveTriviaSyntax::create(Ptr<SyntaxToken> startToken,
                                                                     Ptr<SyntaxToken> regionKeyword,
                                                                     Ptr<SyntaxToken> endOfDirectiveToken,
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
