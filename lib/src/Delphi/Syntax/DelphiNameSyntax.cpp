#include "Delphi/Syntax/DelphiNameSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiNameSyntax::DelphiNameSyntax(Core::Syntax::SyntaxKind syntaxKind) noexcept
    : DelphiTypeSyntax{syntaxKind}
{}

} // end namespace polyglot::Delphi::Syntax
