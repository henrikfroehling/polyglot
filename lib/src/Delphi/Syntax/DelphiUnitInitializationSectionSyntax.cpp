#include "DelphiUnitInitializationSectionSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiUnitInitializationSectionSyntax::DelphiUnitInitializationSectionSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitInitializationSection}
{}

DelphiUnitInitializationSectionSyntax* DelphiUnitInitializationSectionSyntax::create(SyntaxFactory& syntaxFactory) noexcept
{
    auto ptrUnitInitializationSectionSyntax = std::make_unique<DelphiUnitInitializationSectionSyntax>();
    return dynamic_cast<DelphiUnitInitializationSectionSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrUnitInitializationSectionSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
