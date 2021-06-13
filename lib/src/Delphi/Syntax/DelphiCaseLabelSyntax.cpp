#include "Delphi/Syntax/DelphiCaseLabelSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiCaseLabelSyntax::DelphiCaseLabelSyntax(DelphiExpressionSyntax* expression,
                                             Core::Syntax::ISyntaxToken* dotDotToken,
                                             DelphiExpressionSyntax* secondExpression) noexcept
    : DelphiSyntaxNode{SyntaxKind::CaseLabel},
      _pExpression{expression},
      _pDotDotToken{dotDotToken},
      _pSecondExpression{secondExpression}
{}

DelphiCaseLabelSyntax* DelphiCaseLabelSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                     DelphiExpressionSyntax* expression,
                                                     Core::Syntax::ISyntaxToken* dotDotToken,
                                                     DelphiExpressionSyntax* secondExpression) noexcept
{
    assert(expression != nullptr);

    if (dotDotToken != nullptr)
    {
        assert(dotDotToken->syntaxKind() == SyntaxKind::DotDotToken);
        assert(secondExpression != nullptr);
    }

    auto ptrCaseLabelSyntax = std::make_unique<DelphiCaseLabelSyntax>(expression, dotDotToken, secondExpression);
    return static_cast<DelphiCaseLabelSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrCaseLabelSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
