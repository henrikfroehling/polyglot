#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitInterfaceSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitInterfaceSectionSyntax::DelphiUnitInterfaceSectionSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitInterfaceSection},
      _ptrUses{nullptr}
{}

} // end namespace polyglot::CodeAnalysis
