#include "Delphi/Syntax/DelphiPredefinedTypeSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/DelphiSyntaxFacts.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiPredefinedTypeSyntax::DelphiPredefinedTypeSyntax(Core::Syntax::ISyntaxToken* keyword) noexcept
    : DelphiTypeSyntax{SyntaxKind::PredefinedType},
      _pKeyword{keyword}
{}

DelphiPredefinedTypeSyntax* DelphiPredefinedTypeSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                               Core::Syntax::ISyntaxToken* keyword) noexcept
{
    assert(keyword != nullptr);
    assert(DelphiSyntaxFacts::isPredefinedType(keyword->syntaxKind()));

    auto ptrPredefinedTypeSyntax = std::make_unique<DelphiPredefinedTypeSyntax>(keyword);
    return static_cast<DelphiPredefinedTypeSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrPredefinedTypeSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
