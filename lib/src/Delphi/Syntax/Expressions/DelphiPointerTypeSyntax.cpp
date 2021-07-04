#include "Delphi/Syntax/Expressions/DelphiPointerTypeSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiPointerTypeSyntax::DelphiPointerTypeSyntax(ISyntaxToken* caretToken,
                                                 DelphiTypeSyntax* type) noexcept
    : DelphiTypeSyntax{SyntaxKind::PointerType},
      _pCaretToken{caretToken},
      _pType{type}
{
    _position = _pCaretToken->position();
    adjustWidthAndFlags(_pCaretToken);
    adjustWidthAndFlags(_pType);
}

SyntaxVariant DelphiPointerTypeSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pCaretToken);
        case 1: return SyntaxVariant::asNode(_pType);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiPointerTypeSyntax* DelphiPointerTypeSyntax::create(SyntaxFactory& syntaxFactory,
                                                         ISyntaxToken* caretToken,
                                                         DelphiTypeSyntax* type) noexcept
{
    assert(caretToken != nullptr);
    assert(caretToken->syntaxKind() == SyntaxKind::CaretToken);
    assert(type != nullptr);

    auto ptrPointerTypeSyntax = std::make_unique<DelphiPointerTypeSyntax>(caretToken, type);
    return static_cast<DelphiPointerTypeSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrPointerTypeSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
