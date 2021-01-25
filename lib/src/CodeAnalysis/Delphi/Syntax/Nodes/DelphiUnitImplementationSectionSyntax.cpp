#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitImplementationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitImplementationSectionSyntax::DelphiUnitImplementationSectionSyntax(SyntaxToken* implementationKeyword) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitImplementationSection},
      _pImplementationKeyword{implementationKeyword},
      _pUses{nullptr}
{}

} // end namespace polyglot::CodeAnalysis
