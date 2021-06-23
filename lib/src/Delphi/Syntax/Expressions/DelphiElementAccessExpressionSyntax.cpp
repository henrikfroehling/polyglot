#include "Delphi/Syntax/Expressions/DelphiElementAccessExpressionSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiElementAccessExpressionSyntax::DelphiElementAccessExpressionSyntax(DelphiExpressionSyntax* element,
                                                                         DelphiBracketArgumentListSyntax* arguments) noexcept
    : DelphiExpressionSyntax{SyntaxKind::ElementAccessExpression},
      _pElement{element},
      _pArguments{arguments}
{}

SyntaxVariant DelphiElementAccessExpressionSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asNode(_pElement);
        case 1: return SyntaxVariant::asNode(_pArguments);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiElementAccessExpressionSyntax* DelphiElementAccessExpressionSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                                                 DelphiExpressionSyntax* element,
                                                                                 DelphiBracketArgumentListSyntax* arguments) noexcept
{
    assert(element != nullptr);
    assert(arguments != nullptr);

    auto ptrElementAccessExpressionSyntax = std::make_unique<DelphiElementAccessExpressionSyntax>(element, arguments);
    return static_cast<DelphiElementAccessExpressionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrElementAccessExpressionSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
