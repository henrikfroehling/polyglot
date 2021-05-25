#include "Delphi/Syntax/DelphiTryStatementSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiTryStatementSyntax::DelphiTryStatementSyntax() noexcept
    : DelphiStatementSyntax{Core::Syntax::SyntaxKind::TryStatement}
{}

} // end namespace polyglot::Delphi::Syntax
