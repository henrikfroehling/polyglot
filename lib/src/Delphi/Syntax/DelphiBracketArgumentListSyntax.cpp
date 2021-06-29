#include "Delphi/Syntax/DelphiBracketArgumentListSyntax.hpp"
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

DelphiBracketArgumentListSyntax::DelphiBracketArgumentListSyntax(Core::Syntax::ISyntaxToken* openBracket,
                                                                 DelphiSyntaxList* arguments,
                                                                 Core::Syntax::ISyntaxToken* closeBracket) noexcept
    : DelphiSyntaxNode{SyntaxKind::BracketArgumentList},
      _pOpenBracketToken{openBracket},
      _pArguments{arguments},
      _pCloseBracketToken{closeBracket}
{
    _position = _pOpenBracketToken->position();
    adjustWidthAndFlags(_pOpenBracketToken);
    adjustWidthAndFlags(_pArguments);
    adjustWidthAndFlags(_pCloseBracketToken);
}

SyntaxVariant DelphiBracketArgumentListSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pOpenBracketToken);
        case 1: return SyntaxVariant::asList(_pArguments);
        case 2: return SyntaxVariant::asToken(_pCloseBracketToken);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiBracketArgumentListSyntax* DelphiBracketArgumentListSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                                         Core::Syntax::ISyntaxToken* openBracket,
                                                                         DelphiSyntaxList* arguments,
                                                                         Core::Syntax::ISyntaxToken* closeBracket) noexcept
{
    assert(openBracket != nullptr);
    assert(openBracket->syntaxKind() == SyntaxKind::OpenBracketToken);
    assert(arguments != nullptr);
    assert(closeBracket != nullptr);
    assert(closeBracket->syntaxKind() == SyntaxKind::CloseBracketToken);

    auto ptrBracketArgumentListSyntax = std::make_unique<DelphiBracketArgumentListSyntax>(openBracket, arguments, closeBracket);
    return static_cast<DelphiBracketArgumentListSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrBracketArgumentListSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
