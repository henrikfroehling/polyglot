#include "Delphi/Syntax/Statements/DelphiRepeatStatementSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiRepeatStatementSyntax::DelphiRepeatStatementSyntax() noexcept
    : DelphiStatementSyntax{Core::Syntax::SyntaxKind::RepeatStatement}
{}

} // end namespace polyglot::Delphi::Syntax
