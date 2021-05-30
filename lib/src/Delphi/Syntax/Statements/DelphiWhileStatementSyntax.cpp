#include "Delphi/Syntax/Statements/DelphiWhileStatementSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiWhileStatementSyntax::DelphiWhileStatementSyntax() noexcept
    : DelphiStatementSyntax{Core::Syntax::SyntaxKind::WhileStatement}
{}

} // end namespace polyglot::Delphi::Syntax
