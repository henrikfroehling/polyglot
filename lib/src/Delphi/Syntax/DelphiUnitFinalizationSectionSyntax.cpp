#include "DelphiUnitFinalizationSectionSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiUnitFinalizationSectionSyntax::DelphiUnitFinalizationSectionSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitFinalizationSection}
{}

DelphiUnitFinalizationSectionSyntax* DelphiUnitFinalizationSectionSyntax::create(SyntaxFactory& syntaxFactory) noexcept
{
    auto ptrUnitFinalizationSectionSyntax = std::make_unique<DelphiUnitFinalizationSectionSyntax>();
    return dynamic_cast<DelphiUnitFinalizationSectionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrUnitFinalizationSectionSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
