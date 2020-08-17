#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiIdentifierNameSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiIdentifierNameSyntax::DelphiIdentifierNameSyntax(SyntaxTokenPtr identfier) noexcept
    : DelphiSimpleNameSyntax{SyntaxKind::IdentifierName},
      _ptrIdentifier{std::move(identfier)}
{}

} // end namespace polyglot::CodeAnalysis
