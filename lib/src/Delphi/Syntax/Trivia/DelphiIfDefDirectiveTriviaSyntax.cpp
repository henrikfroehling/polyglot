#include "Delphi/Syntax/Trivia/DelphiIfDefDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiIfDefDirectiveTriviaSyntax::DelphiIfDefDirectiveTriviaSyntax(SyntaxKind syntaxKind,
                                                                   ISyntaxToken* startToken,
                                                                   ISyntaxToken* ifDefKeyword,
                                                                   ISyntaxToken* name,
                                                                   ISyntaxToken* endOfDirectiveToken,
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
    adjustWidth(_pStartToken);
    adjustWidth(_pIfDefKeyword);
    adjustWidth(_pName);
    adjustWidth(_pEndOfDirectiveToken);
}

SyntaxVariant DelphiIfDefDirectiveTriviaSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pStartToken);
        case 1: return SyntaxVariant::asToken(_pIfDefKeyword);
        case 2: return SyntaxVariant::asToken(_pName);
        case 3: return SyntaxVariant::asToken(_pEndOfDirectiveToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiIfDefDirectiveTriviaSyntax* DelphiIfDefDirectiveTriviaSyntax::create(SyntaxFactory& syntaxFactory,
                                                                           ISyntaxToken* startToken,
                                                                           ISyntaxToken* ifDefKeyword,
                                                                           ISyntaxToken* name,
                                                                           ISyntaxToken* endOfDirectiveToken,
                                                                           bool isActive,
                                                                           bool isBranchTaken) noexcept
{
    assert(startToken != nullptr);
    assert(ifDefKeyword != nullptr);
    assert(ifDefKeyword->syntaxKind() == SyntaxKind::IfDefDirectiveKeyword);
    assert(name != nullptr);
    assert(endOfDirectiveToken != nullptr);
    assert(endOfDirectiveToken->syntaxKind() == SyntaxKind::EndOfDirectiveToken);

    auto ptrIfDefDirectiveTrivia = std::make_unique<DelphiIfDefDirectiveTriviaSyntax>(SyntaxKind::IfDefDirectiveTrivia, startToken,
                                                                                      ifDefKeyword, name, endOfDirectiveToken,
                                                                                      isActive, isBranchTaken);

    return dynamic_cast<DelphiIfDefDirectiveTriviaSyntax*>(syntaxFactory.addSyntaxTrivia(std::move(ptrIfDefDirectiveTrivia)));
}

} // end namespace polyglot::Delphi::Syntax
