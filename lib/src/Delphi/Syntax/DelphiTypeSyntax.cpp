#include "Delphi/Syntax/DelphiTypeSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiTypeSyntax::DelphiTypeSyntax(Core::Syntax::SyntaxKind syntaxKind) noexcept
    : DelphiExpressionSyntax{syntaxKind}
{}

} // end namespace polyglot::Delphi::Syntax
