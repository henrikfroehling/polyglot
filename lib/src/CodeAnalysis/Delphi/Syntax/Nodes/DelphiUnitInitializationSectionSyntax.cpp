#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInitializationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitInitializationSectionSyntax::DelphiUnitInitializationSectionSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitInitializationSection}
{}

} // end namespace polyglot::CodeAnalysis
