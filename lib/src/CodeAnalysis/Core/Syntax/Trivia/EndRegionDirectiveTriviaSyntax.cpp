#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/EndRegionDirectiveTriviaSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

EndRegionDirectiveTriviaSyntax::EndRegionDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                               SyntaxTokenPtr startToken,
                                                               SyntaxTokenPtr endRegionKeyword,
                                                               SyntaxTokenPtr endOfDirectiveToken,
                                                               bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
    _ptrStartToken{std::move(startToken)},
    _ptrEndRegionKeyword{std::move(endRegionKeyword)},
    _ptrEndOfDirectiveToken{std::move(endOfDirectiveToken)},
    _isActive{isActive}
{}

EndRegionDirectiveTriviaSyntaxPtr EndRegionDirectiveTriviaSyntax::Create(SyntaxTokenPtr startToken,
                                                                         SyntaxTokenPtr endRegionKeyword,
                                                                         SyntaxTokenPtr endOfDirectiveToken,
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
