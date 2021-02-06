#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitFinalizationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitFinalizationSectionSyntax::DelphiUnitFinalizationSectionSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitFinalizationSection}
{}

DelphiUnitFinalizationSectionSyntax* DelphiUnitFinalizationSectionSyntax::create(SyntaxFactory& syntaxFactory) noexcept
{
    auto ptrUnitFinalizationSectionSyntax = std::make_unique<DelphiUnitFinalizationSectionSyntax>();
    return static_cast<DelphiUnitFinalizationSectionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrUnitFinalizationSectionSyntax)));
}

} // end namespace polyglot::CodeAnalysis
