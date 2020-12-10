#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/ElseDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include <cassert>
#include <memory>

namespace polyglot::CodeAnalysis
{

ElseDirectiveTriviaSyntax::ElseDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                     SyntaxToken* startToken,
                                                     SyntaxToken* elseKeyword,
                                                     SyntaxToken* endOfDirectiveToken,
                                                     bool isActive,
                                                     bool isBranchTaken) noexcept
    : BranchingDirectiveTriviaSyntax{syntaxKind},
      _ptrStartToken{startToken},
      _ptrElseKeyword{elseKeyword},
      _ptrEndOfDirectiveToken{endOfDirectiveToken},
      _isActive{isActive},
      _isBranchTaken{isBranchTaken}
{
    _position = _ptrStartToken->position();
}

ElseDirectiveTriviaSyntax* ElseDirectiveTriviaSyntax::create(SyntaxToken* startToken,
                                                             SyntaxToken* elseKeyword,
                                                             SyntaxToken* endOfDirectiveToken,
                                                             bool isActive,
                                                             bool isBranchTaken) noexcept
{
    assert(startToken != nullptr);
    assert(elseKeyword != nullptr);
    assert(elseKeyword->syntaxKind() == SyntaxKind::ElseDirectiveKeyword);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrElseDirectiveTrivia = std::make_unique<ElseDirectiveTriviaSyntax>(SyntaxKind::ElseDirectiveTrivia, startToken,
                                                                              elseKeyword, endOfDirectiveToken,
                                                                              isActive, isBranchTaken);

    return static_cast<ElseDirectiveTriviaSyntax*>(SyntaxPool::addSyntaxTrivia(std::move(ptrElseDirectiveTrivia)));
}

} // end namespace polyglot::CodeAnalysis
