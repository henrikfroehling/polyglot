#include "DelphiProgramHeadSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiProgramHeadSyntax::DelphiProgramHeadSyntax() noexcept
    : DelphiSyntaxNode{Core::Syntax::SyntaxKind::ProgramHead}
{}

} // end namespace polyglot::Delphi::Syntax
