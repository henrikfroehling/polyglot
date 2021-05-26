#include "Delphi/Syntax/DelphiExpressionSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiExpressionSyntax::DelphiExpressionSyntax(Core::Syntax::SyntaxKind syntaxKind) noexcept
    : Core::Syntax::ExpressionSyntax{syntaxKind}
{}

} // end namespace polyglot::Delphi::Syntax
