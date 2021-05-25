#include "Delphi/Syntax/DelphiRaiseStatementSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiRaiseStatementSyntax::DelphiRaiseStatementSyntax() noexcept
    : DelphiStatementSyntax{Core::Syntax::SyntaxKind::RaiseStatement}
{}

} // end namespace polyglot::Delphi::Syntax
