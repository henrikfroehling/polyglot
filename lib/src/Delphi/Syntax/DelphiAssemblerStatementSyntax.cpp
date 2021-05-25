#include "Delphi/Syntax/DelphiAssemblerStatementSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiAssemblerStatementSyntax::DelphiAssemblerStatementSyntax() noexcept
    : DelphiStatementSyntax{Core::Syntax::SyntaxKind::AssemblerStatement}
{}

} // end namespace polyglot::Delphi::Syntax
