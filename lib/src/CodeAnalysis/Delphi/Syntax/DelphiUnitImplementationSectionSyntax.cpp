#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitImplementationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiUnitImplementationSectionSyntax::DelphiUnitImplementationSectionSyntax(SyntaxTokenPtr implementationKeyword) noexcept
    : DelphiSyntaxNode{SyntaxKind::UnitImplementationSection},
      _ptrImplementationKeyword{std::move(implementationKeyword)},
      _ptrUses{nullptr}
{}

} // end namespace polyglot::CodeAnalysis