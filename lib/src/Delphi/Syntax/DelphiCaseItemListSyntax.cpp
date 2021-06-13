#include "Delphi/Syntax/DelphiCaseItemListSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiCaseItemListSyntax::DelphiCaseItemListSyntax(std::vector<Core::Syntax::SyntaxVariant>&& caseItems) noexcept
    : DelphiSyntaxList{Core::Syntax::SyntaxKind::CaseItemList, std::move(caseItems)}
{}

DelphiCaseItemListSyntax* DelphiCaseItemListSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                           std::vector<Core::Syntax::SyntaxVariant>&& caseItems) noexcept
{
    auto ptrCaseItemListSyntax = std::make_unique<DelphiCaseItemListSyntax>(std::move(caseItems));
    return static_cast<DelphiCaseItemListSyntax*>(syntaxFactory.addSyntaxList(std::move(ptrCaseItemListSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
