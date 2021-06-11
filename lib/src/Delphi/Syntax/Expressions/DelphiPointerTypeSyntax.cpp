#include "Delphi/Syntax/Expressions/DelphiPointerTypeSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiPointerTypeSyntax::DelphiPointerTypeSyntax(Core::Syntax::ISyntaxToken* caretToken,
                                                 DelphiTypeSyntax* type) noexcept
    : DelphiTypeSyntax{SyntaxKind::PointerTypeExpression},
      _pCaretToken{caretToken},
      _pType{type}
{}

DelphiPointerTypeSyntax* DelphiPointerTypeSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                         Core::Syntax::ISyntaxToken* caretToken,
                                                         DelphiTypeSyntax* type) noexcept
{
    assert(caretToken != nullptr);
    assert(caretToken->syntaxKind() == SyntaxKind::CaretToken);
    assert(type != nullptr);

    auto ptrPointerTypeSyntax = std::make_unique<DelphiPointerTypeSyntax>(caretToken, type);
    return static_cast<DelphiPointerTypeSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrPointerTypeSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
