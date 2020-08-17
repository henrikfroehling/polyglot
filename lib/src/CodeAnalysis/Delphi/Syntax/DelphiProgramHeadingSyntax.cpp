#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiProgramHeadingSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

DelphiProgramHeadingSyntax::DelphiProgramHeadingSyntax() noexcept
    : DelphiSyntaxNode{SyntaxKind::ProgramHeading}
{}

} // end namespace polyglot::CodeAnalysis
