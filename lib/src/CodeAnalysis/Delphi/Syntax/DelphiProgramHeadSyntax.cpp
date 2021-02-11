#include "CodeAnalysis/Delphi/Syntax/DelphiProgramHeadSyntax.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiProgramHeadSyntax::DelphiProgramHeadSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::ProgramHead}
{}

} // end namespace polyglot::CodeAnalysis
