#include "Delphi/Syntax/Expressions/DelphiSetElementsConstructorSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/DelphiSyntaxList.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiSetElementsConstructorSyntax::DelphiSetElementsConstructorSyntax(Core::Syntax::ISyntaxToken* openBracketToken,
                                                                       DelphiSyntaxList* elements,
                                                                       Core::Syntax::ISyntaxToken* closeBracketToken) noexcept
    : DelphiSetConstructorSyntax{SyntaxKind::SetElementsConstructor, openBracketToken, closeBracketToken},
      _pElements{elements}
{
    _position = _pOpenBracketToken->position();
    adjustWidthAndFlags(_pOpenBracketToken);
    adjustWidthAndFlags(_pElements);
    adjustWidthAndFlags(_pCloseBracketToken);
}

SyntaxVariant DelphiSetElementsConstructorSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pOpenBracketToken);
        case 1: return SyntaxVariant::asList(_pElements);
        case 2: return SyntaxVariant::asToken(_pCloseBracketToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiSetElementsConstructorSyntax* DelphiSetElementsConstructorSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                                               Core::Syntax::ISyntaxToken* openBracketToken,
                                                                               DelphiSyntaxList* elements,
                                                                               Core::Syntax::ISyntaxToken* closeBracketToken) noexcept
{
    assert(openBracketToken != nullptr);
    assert(openBracketToken->syntaxKind() == SyntaxKind::OpenBracketToken);
    assert(elements != nullptr);
    assert(closeBracketToken != nullptr);
    assert(closeBracketToken->syntaxKind() == SyntaxKind::CloseBracketToken);

    auto ptrSetElementsConstructorSyntax = std::make_unique<DelphiSetElementsConstructorSyntax>(openBracketToken, elements, closeBracketToken);
    return static_cast<DelphiSetElementsConstructorSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrSetElementsConstructorSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
