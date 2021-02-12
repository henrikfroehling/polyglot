#include "CodeAnalysis/Core/Syntax/Trivia/IfEndDirectiveTriviaSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

IfEndDirectiveTriviaSyntax::IfEndDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                       LanguageSyntaxToken* startToken,
                                                       LanguageSyntaxToken* ifEndKeyword,
                                                       LanguageSyntaxToken* endOfDirectiveToken,
                                                       bool isActive) noexcept
    : DirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pIfEndKeyword{ifEndKeyword},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive}
{
    _position = _pStartToken->position();
    adjustWidthAndFlags(_pStartToken);
    adjustWidthAndFlags(_pIfEndKeyword);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
}

LanguageSyntaxNode* IfEndDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pStartToken;
        case 1: return _pIfEndKeyword;
        case 2: return _pEndOfDirectiveToken;
    }

    throw std::out_of_range{"index out of range"};
}

IfEndDirectiveTriviaSyntax* IfEndDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                               LanguageSyntaxToken* startToken,
                                                               LanguageSyntaxToken* ifEndKeyword,
                                                               LanguageSyntaxToken* endOfDirectiveToken,
                                                               bool isActive) noexcept
{
    assert(startToken != nullptr);
    assert(ifEndKeyword != nullptr);
    assert(ifEndKeyword->syntaxKind() == SyntaxKind::IfEndDirectiveKeyword);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrIfEndDirectiveTrivia = std::make_unique<IfEndDirectiveTriviaSyntax>(SyntaxKind::IfEndDirectiveTrivia, startToken,
                                                                                ifEndKeyword, endOfDirectiveToken, isActive);

    return static_cast<IfEndDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrIfEndDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
