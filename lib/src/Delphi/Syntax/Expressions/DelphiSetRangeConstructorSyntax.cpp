#include "Delphi/Syntax/Expressions/DelphiSetRangeConstructorSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiSetRangeConstructorSyntax::DelphiSetRangeConstructorSyntax(Core::Syntax::ISyntaxToken* openBracketToken,
                                                                 DelphiExpressionSyntax* firstElement,
                                                                 Core::Syntax::ISyntaxToken* dotDotToken,
                                                                 DelphiExpressionSyntax* lastElement,
                                                                 Core::Syntax::ISyntaxToken* closeBracketToken) noexcept
    : DelphiSetConstructorSyntax{SyntaxKind::SetRangeConstructor, openBracketToken, closeBracketToken},
      _pFirstElement{firstElement},
      _pDotDotToken{dotDotToken},
      _pLastElement{lastElement}
{}

SyntaxVariant DelphiSetRangeConstructorSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pOpenBracketToken);
        case 1: return SyntaxVariant::asNode(_pFirstElement);
        case 2: return SyntaxVariant::asToken(_pDotDotToken);
        case 3: return SyntaxVariant::asNode(_pLastElement);
        case 4: return SyntaxVariant::asToken(_pCloseBracketToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiSetRangeConstructorSyntax* DelphiSetRangeConstructorSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                                         Core::Syntax::ISyntaxToken* openBracketToken,
                                                                         DelphiExpressionSyntax* firstElement,
                                                                         Core::Syntax::ISyntaxToken* dotDotToken,
                                                                         DelphiExpressionSyntax* lastElement,
                                                                         Core::Syntax::ISyntaxToken* closeBracketToken) noexcept
{
    assert(openBracketToken != nullptr);
    assert(openBracketToken->syntaxKind() == SyntaxKind::OpenBracketToken);
    assert(firstElement != nullptr);
    assert(dotDotToken != nullptr);
    assert(dotDotToken->syntaxKind() == SyntaxKind::DotDotToken);
    assert(lastElement != nullptr);
    assert(closeBracketToken != nullptr);
    assert(closeBracketToken->syntaxKind() == SyntaxKind::CloseBracketToken);

    auto ptrSetRangeConstructorSyntax = std::make_unique<DelphiSetRangeConstructorSyntax>(openBracketToken, firstElement, dotDotToken,
                                                                                          lastElement, closeBracketToken);

    return static_cast<DelphiSetRangeConstructorSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrSetRangeConstructorSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
