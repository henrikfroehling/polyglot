#include "CodeAnalysis/Core/Syntax/Trivia/IfDefDirectiveTriviaSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

IfDefDirectiveTriviaSyntax::IfDefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                       LanguageSyntaxToken* startToken,
                                                       LanguageSyntaxToken* ifDefKeyword,
                                                       LanguageSyntaxToken* name,
                                                       LanguageSyntaxToken* endOfDirectiveToken,
                                                       bool isActive,
                                                       bool isBranchTaken) noexcept
    : ConditionalDirectiveTriviaSyntax{syntaxKind},
      _pStartToken{startToken},
      _pIfDefKeyword{ifDefKeyword},
      _pName{name},
      _pEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive},
      _isBranchTaken{isBranchTaken}
{
    _position = _pStartToken->position();
    adjustWidthAndFlags(_pStartToken);
    adjustWidthAndFlags(_pIfDefKeyword);
    adjustWidthAndFlags(_pName);
    adjustWidthAndFlags(_pEndOfDirectiveToken);
}

LanguageSyntaxNode* IfDefDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pStartToken;
        case 1: return _pIfDefKeyword;
        case 2: return _pName;
        case 3: return _pEndOfDirectiveToken;
    }

    throw std::out_of_range{"index out of range"};
}

IfDefDirectiveTriviaSyntax* IfDefDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                               LanguageSyntaxToken* startToken,
                                                               LanguageSyntaxToken* ifDefKeyword,
                                                               LanguageSyntaxToken* name,
                                                               LanguageSyntaxToken* endOfDirectiveToken,
                                                               bool isActive,
                                                               bool isBranchTaken) noexcept
{
    assert(startToken != nullptr);
    assert(ifDefKeyword != nullptr);
    assert(ifDefKeyword->syntaxKind() == SyntaxKind::IfDefDirectiveKeyword);
    assert(name != nullptr);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrIfDefDirectiveTrivia = std::make_unique<IfDefDirectiveTriviaSyntax>(SyntaxKind::IfDefDirectiveTrivia, startToken,
                                                                                ifDefKeyword, name, endOfDirectiveToken,
                                                                                isActive, isBranchTaken);

    return static_cast<IfDefDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrIfDefDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
