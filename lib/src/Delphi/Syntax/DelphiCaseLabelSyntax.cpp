#include "Delphi/Syntax/DelphiCaseLabelSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiCaseLabelSyntax::DelphiCaseLabelSyntax(DelphiExpressionSyntax* expression,
                                             ISyntaxToken* dotDotToken,
                                             DelphiExpressionSyntax* secondExpression) noexcept
    : DelphiSyntaxNode{SyntaxKind::CaseLabel},
      _pExpression{expression},
      _pDotDotToken{dotDotToken},
      _pSecondExpression{secondExpression}
{}

SyntaxVariant DelphiCaseLabelSyntax::child(pg_size index) const
{
    switch (childCount())
    {
        case 2:
        {
            switch (index)
            {
                case 0: return SyntaxVariant::asNode(_pExpression);
            }
        }
        case 3:
        {
            switch (index)
            {
                case 0: return SyntaxVariant::asNode(_pExpression);
                case 1: return SyntaxVariant::asToken(_pDotDotToken);
                case 2: return SyntaxVariant::asNode(_pSecondExpression);
            }
        }
    }

    throw std::out_of_range{"index out of range"};
}

DelphiCaseLabelSyntax* DelphiCaseLabelSyntax::create(SyntaxFactory& syntaxFactory,
                                                     DelphiExpressionSyntax* expression,
                                                     ISyntaxToken* dotDotToken,
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
