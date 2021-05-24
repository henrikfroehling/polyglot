#include "Delphi/Syntax/DelphiSyntaxList.hpp"
#include <vector>
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiSyntaxList::DelphiSyntaxList(Core::Syntax::SyntaxKind syntaxKind) noexcept
    : Core::Syntax::SyntaxList{syntaxKind, std::vector<Core::Syntax::SyntaxVariant>{}}
{}

DelphiSyntaxList::DelphiSyntaxList(Core::Syntax::SyntaxKind syntaxKind,
                                   std::vector<Core::Syntax::SyntaxVariant>&& children) noexcept
    : Core::Syntax::SyntaxList{syntaxKind, std::move(children)}
{}

} // end namespace polyglot::Delphi::Syntax
