#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitImplementationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitImplementationSectionSyntax::DelphiUnitImplementationSectionSyntax(SyntaxToken* implementationKeyword) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitImplementationSection},
      _ptrImplementationKeyword{implementationKeyword},
      _ptrUses{nullptr}
{}

} // end namespace polyglot::CodeAnalysis
