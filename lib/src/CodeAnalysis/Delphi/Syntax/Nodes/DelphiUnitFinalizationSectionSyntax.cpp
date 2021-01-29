#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitFinalizationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitFinalizationSectionSyntax::DelphiUnitFinalizationSectionSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitFinalizationSection}
{}

DelphiUnitFinalizationSectionSyntax* DelphiUnitFinalizationSectionSyntax::create() noexcept
{
    auto ptrUnitFinalizationSectionSyntax = std::make_unique<DelphiUnitFinalizationSectionSyntax>();
    return static_cast<DelphiUnitFinalizationSectionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrUnitFinalizationSectionSyntax)));
}

} // end namespace polyglot::CodeAnalysis
