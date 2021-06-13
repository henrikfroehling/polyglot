#include "Delphi/Syntax/DelphiCaseItemSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiCaseItemSyntax::DelphiCaseItemSyntax(DelphiCaseLabelListSyntax* caseLabels,
                                           ISyntaxToken* colonToken,
                                           DelphiStatementSyntax* statement) noexcept
    : DelphiSyntaxNode{SyntaxKind::CaseItem},
      _pCaseLabels{caseLabels},
      _pColonToken{colonToken},
      _pStatement{statement}
{}

SyntaxVariant DelphiCaseItemSyntax::child(pg_size index) const
{
    switch (index)
    {
        case 0: return SyntaxVariant::asList(_pCaseLabels);
        case 1: return SyntaxVariant::asToken(_pColonToken);
        case 2: return SyntaxVariant::asNode(_pStatement);
    }

    throw std::out_of_range{"index out of range"};
}

DelphiCaseItemSyntax* DelphiCaseItemSyntax::create(SyntaxFactory& syntaxFactory,
                                                   DelphiCaseLabelListSyntax* caseLabels,
                                                   ISyntaxToken* colonToken,
                                                   DelphiStatementSyntax* statement) noexcept
{
    assert(caseLabels != nullptr);
    assert(colonToken != nullptr);
    assert(colonToken->syntaxKind() == SyntaxKind::ColonToken);
    assert(statement != nullptr);

    auto ptrCaseItemSyntax = std::make_unique<DelphiCaseItemSyntax>(caseLabels, colonToken, statement);
    return static_cast<DelphiCaseItemSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrCaseItemSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
