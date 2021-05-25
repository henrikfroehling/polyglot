#include "Delphi/Syntax/DelphiCaseStatementSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiCaseStatementSyntax::DelphiCaseStatementSyntax() noexcept
    : DelphiStatementSyntax{Core::Syntax::SyntaxKind::CaseStatement}
{}

} // end namespace polyglot::Delphi::Syntax
