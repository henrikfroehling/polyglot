#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitImplementationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitImplementationSectionSyntax::DelphiUnitImplementationSectionSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitImplementationSection},
      _ptrUses{nullptr}
{}

} // end namespace polyglot::CodeAnalysis
