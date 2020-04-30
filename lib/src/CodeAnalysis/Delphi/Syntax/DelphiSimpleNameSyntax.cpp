#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSimpleNameSyntax.hpp"

namespace polyglot::CodeAnalysis
{

DelphiSimpleNameSyntax::DelphiSimpleNameSyntax(SyntaxKind syntaxKind,
                                               SyntaxToken identifier) noexcept
    : DelphiNameSyntax{syntaxKind},
      _identifier{identifier}
{}

} // end namespace polyglot::CodeAnalysis
