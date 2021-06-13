#include "Delphi/Syntax/Expressions/DelphiPredefinedTypeSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/DelphiSyntaxFacts.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiPredefinedTypeSyntax::DelphiPredefinedTypeSyntax(ISyntaxToken* keyword) noexcept
    : DelphiTypeSyntax{SyntaxKind::PredefinedType},
      _pKeyword{keyword}
{}

SyntaxVariant DelphiPredefinedTypeSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asToken(_pKeyword);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiPredefinedTypeSyntax* DelphiPredefinedTypeSyntax::create(SyntaxFactory& syntaxFactory,
                                                               ISyntaxToken* keyword) noexcept
{
    assert(keyword != nullptr);
    assert(DelphiSyntaxFacts::isPredefinedType(keyword->syntaxKind()));

    auto ptrPredefinedTypeSyntax = std::make_unique<DelphiPredefinedTypeSyntax>(keyword);
    return static_cast<DelphiPredefinedTypeSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrPredefinedTypeSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
