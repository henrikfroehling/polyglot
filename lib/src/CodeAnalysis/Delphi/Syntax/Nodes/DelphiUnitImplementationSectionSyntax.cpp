#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitImplementationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitImplementationSectionSyntax::DelphiUnitImplementationSectionSyntax(SyntaxToken* implementationKeyword) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitImplementationSection},
      _pImplementationKeyword{implementationKeyword},
      _pUses{nullptr}
{}

} // end namespace polyglot::CodeAnalysis
