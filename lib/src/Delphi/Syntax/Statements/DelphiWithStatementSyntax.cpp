#include "Delphi/Syntax/Statements/DelphiWithStatementSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiWithStatementSyntax::DelphiWithStatementSyntax() noexcept
    : DelphiStatementSyntax{Core::Syntax::SyntaxKind::WithStatement}
{}

} // end namespace polyglot::Delphi::Syntax
