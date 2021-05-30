#include "Delphi/Syntax/Expressions/DelphiIdentifierNameSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiIdentifierNameSyntax::DelphiIdentifierNameSyntax(ISyntaxToken* identfier) noexcept
    : DelphiSimpleNameSyntax{SyntaxKind::IdentifierName},
      _pIdentifier{identfier}
{
    _position = _pIdentifier->position();
    adjustWidthAndFlags(_pIdentifier);
}

SyntaxVariant DelphiIdentifierNameSyntax::child(pg_size index) const
{
    if (index == 0)
        return SyntaxVariant::asToken(_pIdentifier);

    throw std::out_of_range{"index out of range"};
}

DelphiIdentifierNameSyntax* DelphiIdentifierNameSyntax::create(SyntaxFactory& syntaxFactory,
                                                               ISyntaxToken* identifier) noexcept
{
    assert(identifier != nullptr);
    assert(identifier->syntaxKind() == SyntaxKind::IdentifierToken);

    auto ptrIdentifierName = std::make_unique<DelphiIdentifierNameSyntax>(identifier);
    return static_cast<DelphiIdentifierNameSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrIdentifierName)));
}

} // end namespace polyglot::Delphi::Syntax
