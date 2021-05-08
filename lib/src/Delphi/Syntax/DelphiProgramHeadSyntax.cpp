#include "DelphiProgramHeadSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiProgramHeadSyntax::DelphiProgramHeadSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::ProgramHead}
{}

} // end namespace polyglot::Delphi::Syntax
