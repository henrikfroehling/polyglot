#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInitializationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitInitializationSectionSyntax::DelphiUnitInitializationSectionSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitInitializationSection}
{}

DelphiUnitInitializationSectionSyntax* DelphiUnitInitializationSectionSyntax::create(SyntaxFactory& syntaxFactory) noexcept
{
    auto ptrUnitInitializationSectionSyntax = std::make_unique<DelphiUnitInitializationSectionSyntax>();
    return static_cast<DelphiUnitInitializationSectionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrUnitInitializationSectionSyntax)));
}

} // end namespace polyglot::CodeAnalysis
