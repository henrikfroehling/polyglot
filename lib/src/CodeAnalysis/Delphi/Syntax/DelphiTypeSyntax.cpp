#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiTypeSyntax.hpp"

namespace polyglot::CodeAnalysis
{

DelphiTypeSyntax::DelphiTypeSyntax(SyntaxKind syntaxKind) noexcept
    : DelphiExpressionSyntax{syntaxKind}
{}

} // end namespace polyglot::CodeAnalysis
