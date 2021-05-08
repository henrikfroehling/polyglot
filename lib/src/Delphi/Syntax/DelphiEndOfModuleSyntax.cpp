#include "DelphiEndOfModuleSyntax.hpp"
#include <cassert>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiEndOfModuleSyntax::DelphiEndOfModuleSyntax(ISyntaxToken* endKeyword,
                                                 ISyntaxToken* dotToken) noexcept
    : DelphiSyntaxNode{SyntaxKind::EndOfModule},
      _pEndKeyword{endKeyword},
      _pDotToken{dotToken}
{
    _position = _pEndKeyword->position();
    adjustWidthAndFlags(_pEndKeyword);
    _pEndKeyword->setChildNumber(0);
    adjustWidthAndFlags(_pDotToken);
    _pDotToken->setChildNumber(1);
}

ISyntaxNode* DelphiEndOfModuleSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pEndKeyword;
        case 1: return _pDotToken;
    }

    throw std::out_of_range{"index out of range"};
}

DelphiEndOfModuleSyntax* DelphiEndOfModuleSyntax::create(SyntaxFactory& syntaxFactory,
                                                         ISyntaxToken* endKeyword,
                                                         ISyntaxToken* dotToken) noexcept
{
    assert(endKeyword != nullptr);
    assert(endKeyword->syntaxKind() == SyntaxKind::EndKeyword);
    assert(dotToken != nullptr);
    assert(dotToken->syntaxKind() == SyntaxKind::DotToken);

    auto ptrEndOfModuleSyntax = std::make_unique<DelphiEndOfModuleSyntax>(endKeyword, dotToken);
    return dynamic_cast<DelphiEndOfModuleSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrEndOfModuleSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
