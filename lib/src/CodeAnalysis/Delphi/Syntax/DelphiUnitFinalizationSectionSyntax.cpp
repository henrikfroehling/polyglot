#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitFinalizationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitFinalizationSectionSyntax::DelphiUnitFinalizationSectionSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitFinalizationSection}
{}

} // end namespace polyglot::CodeAnalysis
