#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/ElseDirectiveTriviaSyntax.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

ElseDirectiveTriviaSyntax::ElseDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                     SyntaxTokenPtr startToken,
                                                     SyntaxTokenPtr elseKeyword,
                                                     SyntaxTokenPtr endOfDirectiveToken,
                                                     bool isActive,
                                                     bool isBranchTaken) noexcept
    : BranchingDirectiveTriviaSyntax{syntaxKind},
      _ptrStartToken{std::move(startToken)},
      _ptrElseKeyword{std::move(elseKeyword)},
      _ptrEndOfDirectiveToken{std::move(endOfDirectiveToken)},
      _isActive{isActive},
      _isBranchTaken{isBranchTaken}
{}

ElseDirectiveTriviaSyntaxPtr ElseDirectiveTriviaSyntax::Create(SyntaxTokenPtr startToken,
                                                               SyntaxTokenPtr elseKeyword,
                                                               SyntaxTokenPtr endOfDirectiveToken,
                                                               bool isActive,
                                                               bool isBranchTaken) noexcept
{
    assert(startToken != nullptr);
    assert(elseKeyword != nullptr);
    assert(elseKeyword->syntaxKind() == SyntaxKind::ElseDirectiveKeyword);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    return std::make_shared<ElseDirectiveTriviaSyntax>(SyntaxKind::ElseDirectiveTrivia, std::move(startToken),
                                                       std::move(elseKeyword), std::move(endOfDirectiveToken),
                                                       isActive, isBranchTaken);
}

} // end namespace polyglot::CodeAnalysis
