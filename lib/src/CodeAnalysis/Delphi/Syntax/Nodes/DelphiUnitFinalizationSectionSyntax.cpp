#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitFinalizationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/SyntaxPool.hpp"

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
