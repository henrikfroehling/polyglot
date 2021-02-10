#include "CodeAnalysis/Delphi/Syntax/Expressions/DelphiEndOfModuleExpressionSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

DelphiEndOfModuleExpressionSyntax::DelphiEndOfModuleExpressionSyntax(LanguageSyntaxToken* endKeyword,
                                                                     LanguageSyntaxToken* dotToken) noexcept
    : DelphiExpressionSyntax{SyntaxKind::EndOfModuleExpression},
      _pEndKeyword{endKeyword},
      _pDotToken{dotToken}
{
    _position = _pEndKeyword->position();
    adjustWidthAndFlags(_pEndKeyword);
    adjustWidthAndFlags(_pDotToken);
}

DelphiEndOfModuleExpressionSyntax* DelphiEndOfModuleExpressionSyntax::create(SyntaxFactory& syntaxFactory,
                                                                             LanguageSyntaxToken* endKeyword,
                                                                             LanguageSyntaxToken* dotToken) noexcept
{
    assert(endKeyword != nullptr);
    assert(endKeyword->syntaxKind() == SyntaxKind::EndKeyword);
    assert(dotToken != nullptr);
    assert(dotToken->syntaxKind() == SyntaxKind::DotToken);

    auto ptrEndOfModuleExpressionSyntax = std::make_unique<DelphiEndOfModuleExpressionSyntax>(endKeyword, dotToken);
    return static_cast<DelphiEndOfModuleExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrEndOfModuleExpressionSyntax)));
}

} // end namespace polyglot::CodeAnalysis
