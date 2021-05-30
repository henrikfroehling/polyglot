#include "Delphi/Syntax/Statements/DelphiForStatementSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiForStatementSyntax::DelphiForStatementSyntax() noexcept
    : DelphiStatementSyntax{Core::Syntax::SyntaxKind::ForStatement}
{}

} // end namespace polyglot::Delphi::Syntax
