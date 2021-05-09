#include "DelphiSyntaxList.hpp"
#include <vector>
#include "polyglot/Core/Syntax/SyntaxNodeOrToken.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiSyntaxList::DelphiSyntaxList(Core::Syntax::SyntaxKind syntaxKind) noexcept
    : Core::Syntax::SyntaxList{ syntaxKind, std::vector<Core::Syntax::SyntaxNodeOrToken>{}}
{}

} // end namespace polyglot::Delphi::Syntax
