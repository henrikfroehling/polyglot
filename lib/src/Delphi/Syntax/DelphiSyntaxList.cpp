#include "Delphi/Syntax/DelphiSyntaxList.hpp"
#include <vector>
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiSyntaxList::DelphiSyntaxList(Core::Syntax::SyntaxKind syntaxKind) noexcept
    : Core::Syntax::SyntaxList{syntaxKind, std::vector<Core::Syntax::SyntaxVariant>{}}
{}

DelphiSyntaxList::DelphiSyntaxList(Core::Syntax::SyntaxKind syntaxKind,
                                   std::vector<Core::Syntax::SyntaxVariant>&& children) noexcept
    : Core::Syntax::SyntaxList{syntaxKind, std::move(children)}
{}

DelphiSyntaxList* DelphiSyntaxList::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                           Core::Syntax::SyntaxKind syntaxKind,
                                           std::vector<Core::Syntax::SyntaxVariant>&& children) noexcept
{
    auto ptrSyntaxList = std::make_unique<DelphiSyntaxList>(syntaxKind, std::move(children));
    return static_cast<DelphiSyntaxList*>(syntaxFactory.addSyntaxList(std::move(ptrSyntaxList)));
}

} // end namespace polyglot::Delphi::Syntax
