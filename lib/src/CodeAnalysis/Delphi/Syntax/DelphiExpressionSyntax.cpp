#include "CodeAnalysis/Delphi/Syntax/DelphiExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

DelphiExpressionSyntax::DelphiExpressionSyntax(SyntaxKind syntaxKind) noexcept
    : ExpressionSyntax{syntaxKind}
{}

} // end namespace polyglot::CodeAnalysis
