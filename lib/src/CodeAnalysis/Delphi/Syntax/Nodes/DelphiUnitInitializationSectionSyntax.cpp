#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInitializationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitInitializationSectionSyntax::DelphiUnitInitializationSectionSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitInitializationSection}
{}

DelphiUnitInitializationSectionSyntax* DelphiUnitInitializationSectionSyntax::create() noexcept
{
    auto ptrUnitInitializationSectionSyntax = std::make_unique<DelphiUnitInitializationSectionSyntax>();
    return static_cast<DelphiUnitInitializationSectionSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrUnitInitializationSectionSyntax)));
}

} // end namespace polyglot::CodeAnalysis
