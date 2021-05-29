#include "Delphi/Syntax/Expressions/DelphiNameExpressionSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiNameExpressionSyntax::DelphiNameExpressionSyntax(Core::Syntax::SyntaxKind syntaxKind) noexcept
    : DelphiTypeExpressionSyntax{syntaxKind}
{}

} // end namespace polyglot::Delphi::Syntax
