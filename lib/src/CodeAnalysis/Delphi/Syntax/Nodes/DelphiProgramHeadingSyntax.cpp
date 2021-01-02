#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiProgramHeadingSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiProgramHeadingSyntax::DelphiProgramHeadingSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::ProgramHeading}
{}

} // end namespace polyglot::CodeAnalysis
