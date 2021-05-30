#include "Delphi/Syntax/DelphiEndOfModuleExpressionSyntax.hpp"
#include <cassert>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::ISyntaxToken;
using Core::Syntax::SyntaxFactory;
using Core::Syntax::SyntaxKind;
using Core::Syntax::SyntaxVariant;

DelphiEndOfModuleExpressionSyntax::DelphiEndOfModuleExpressionSyntax(ISyntaxToken* endKeyword,
                                                                     ISyntaxToken* dotToken) noexcept
    : DelphiExpressionSyntax{SyntaxKind::EndOfModuleExpression},
      _pEndKeyword{endKeyword},
      _pDotToken{dotToken}
{
    _position = _pEndKeyword->position();
    adjustWidthAndFlags(_pEndKeyword);
    adjustWidthAndFlags(_pDotToken);
}

SyntaxVariant DelphiEndOfModuleExpressionSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pEndKeyword);
        case 1: return SyntaxVariant::asToken(_pDotToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiEndOfModuleExpressionSyntax* DelphiEndOfModuleExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                                             ISyntaxToken* endKeyword,
                                                                             ISyntaxToken* dotToken) noexcept
{
    assert(endKeyword != nullptr);
    assert(endKeyword->syntaxKind() == SyntaxKind::EndKeyword);
    assert(dotToken != nullptr);
    assert(dotToken->syntaxKind() == SyntaxKind::DotToken);

    auto ptrEndOfModuleSyntax = std::make_unique<DelphiEndOfModuleExpressionSyntax>(endKeyword, dotToken);
    return static_cast<DelphiEndOfModuleExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrEndOfModuleSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
