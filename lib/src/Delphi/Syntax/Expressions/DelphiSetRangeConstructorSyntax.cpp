#include "Delphi/Syntax/Expressions/DelphiSetRangeConstructorSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/Expressions/DelphiRangeExpressionSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiSetRangeConstructorSyntax::DelphiSetRangeConstructorSyntax(Core::Syntax::ISyntaxToken* openBracketToken,
                                                                 DelphiRangeExpressionSyntax* setRange,
                                                                 Core::Syntax::ISyntaxToken* closeBracketToken) noexcept
    : DelphiSetConstructorSyntax{SyntaxKind::SetRangeConstructor, openBracketToken, closeBracketToken},
      _pSetRange{setRange}
{}

SyntaxVariant DelphiSetRangeConstructorSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pOpenBracketToken);
        case 1: return SyntaxVariant::asNode(_pSetRange);
        case 2: return SyntaxVariant::asToken(_pCloseBracketToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiSetRangeConstructorSyntax* DelphiSetRangeConstructorSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                                         Core::Syntax::ISyntaxToken* openBracketToken,
                                                                         DelphiRangeExpressionSyntax* setRange,
                                                                         Core::Syntax::ISyntaxToken* closeBracketToken) noexcept
{
    assert(openBracketToken != nullptr);
    assert(openBracketToken->syntaxKind() == SyntaxKind::OpenBracketToken);
    assert(setRange != nullptr);
    assert(closeBracketToken != nullptr);
    assert(closeBracketToken->syntaxKind() == SyntaxKind::CloseBracketToken);

    auto ptrSetRangeConstructorSyntax = std::make_unique<DelphiSetRangeConstructorSyntax>(openBracketToken, setRange, closeBracketToken);
    return static_cast<DelphiSetRangeConstructorSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrSetRangeConstructorSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
