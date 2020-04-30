#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiIdentifierNameSyntax.hpp"

namespace polyglot::CodeAnalysis
{

DelphiIdentifierNameSyntax::DelphiIdentifierNameSyntax(SyntaxKind syntaxKind,
                                                       SyntaxToken identifier) noexcept
    : DelphiSimpleNameSyntax{syntaxKind, identifier}
{}

} // end namespace polyglot::CodeAnalysis
