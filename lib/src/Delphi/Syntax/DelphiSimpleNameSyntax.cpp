#include "Delphi/Syntax/DelphiSimpleNameSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiSimpleNameSyntax::DelphiSimpleNameSyntax(Core::Syntax::SyntaxKind syntaxKind) noexcept
    : DelphiNameSyntax{syntaxKind}
{}

} // end namespace polyglot::Delphi::Syntax
