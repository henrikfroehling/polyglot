#include "Delphi/Syntax/DelphiCaseLabelListSyntax.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

DelphiCaseLabelListSyntax::DelphiCaseLabelListSyntax(std::vector<Core::Syntax::SyntaxVariant>&& labels) noexcept
    : DelphiSyntaxList{Core::Syntax::SyntaxKind::CaseLabelList, std::move(labels)}
{}

DelphiCaseLabelListSyntax* DelphiCaseLabelListSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                             std::vector<Core::Syntax::SyntaxVariant>&& labels) noexcept
{
    auto ptrCaseLabelListSyntax = std::make_unique<DelphiCaseLabelListSyntax>(std::move(labels));
    return static_cast<DelphiCaseLabelListSyntax*>(syntaxFactory.addSyntaxList(std::move(ptrCaseLabelListSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
