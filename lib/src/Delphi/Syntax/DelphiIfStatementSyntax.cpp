#include "Delphi/Syntax/DelphiIfStatementSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiIfStatementSyntax::DelphiIfStatementSyntax() noexcept
    : DelphiStatementSyntax{Core::Syntax::SyntaxKind::IfStatement}
{}

} // end namespace polyglot::Delphi::Syntax
