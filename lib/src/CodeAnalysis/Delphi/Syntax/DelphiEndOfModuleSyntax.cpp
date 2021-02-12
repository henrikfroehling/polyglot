#include "CodeAnalysis/Delphi/Syntax/DelphiEndOfModuleSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

DelphiEndOfModuleSyntax::DelphiEndOfModuleSyntax(LanguageSyntaxToken* endKeyword,
                                                 LanguageSyntaxToken* dotToken) noexcept
    : DelphiSyntaxNode{SyntaxKind::EndOfModule},
      _pEndKeyword{endKeyword},
      _pDotToken{dotToken}
{
    _position = _pEndKeyword->position();
    adjustWidthAndFlags(_pEndKeyword);
    adjustWidthAndFlags(_pDotToken);
}

LanguageSyntaxNode* DelphiEndOfModuleSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return _pEndKeyword;
        case 1: return _pDotToken;
    }

    throw std::out_of_range{"index out of range"};
}

DelphiEndOfModuleSyntax* DelphiEndOfModuleSyntax::create(SyntaxFactory& syntaxFactory,
                                                         LanguageSyntaxToken* endKeyword,
                                                         LanguageSyntaxToken* dotToken) noexcept
{
    assert(endKeyword != nullptr);
    assert(endKeyword->syntaxKind() == SyntaxKind::EndKeyword);
    assert(dotToken != nullptr);
    assert(dotToken->syntaxKind() == SyntaxKind::DotToken);

    auto ptrEndOfModuleSyntax = std::make_unique<DelphiEndOfModuleSyntax>(endKeyword, dotToken);
    return static_cast<DelphiEndOfModuleSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrEndOfModuleSyntax)));
}

} // end namespace polyglot::CodeAnalysis
