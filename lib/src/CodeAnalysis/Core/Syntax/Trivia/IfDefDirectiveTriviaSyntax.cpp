#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/IfDefDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

IfDefDirectiveTriviaSyntax::IfDefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                       SyntaxToken* startToken,
                                                       SyntaxToken* ifDefKeyword,
                                                       SyntaxToken* name,
                                                       SyntaxToken* endOfDirectiveToken,
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
}

IfDefDirectiveTriviaSyntax* IfDefDirectiveTriviaSyntax::create(SyntaxToken* startToken,
                                                               SyntaxToken* ifDefKeyword,
                                                               SyntaxToken* name,
                                                               SyntaxToken* endOfDirectiveToken,
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

    return static_cast<IfDefDirectiveTriviaSyntax*>(SyntaxPool::addSyntaxTrivia(std::move(ptrIfDefDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
