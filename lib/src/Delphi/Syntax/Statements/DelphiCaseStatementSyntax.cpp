#include "Delphi/Syntax/Statements/DelphiCaseStatementSyntax.hpp"
#include <cassert>
#include <memory>
#include <stdexcept>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Delphi/Syntax/Expressions/DelphiExpressionSyntax.hpp"
#include "Delphi/Syntax/DelphiCaseElseClauseSyntax.hpp"
#include "Delphi/Syntax/DelphiCaseItemListSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

using namespace Core::Syntax;

DelphiCaseStatementSyntax::DelphiCaseStatementSyntax(ISyntaxToken* caseKeyword,
                                                     DelphiExpressionSyntax* selectorExpression,
                                                     ISyntaxToken* ofKeyword,
                                                     DelphiCaseItemListSyntax* caseItems,
                                                     ISyntaxToken* endKeyword,
                                                     ISyntaxToken* semiColonToken,
                                                     DelphiCaseElseClauseSyntax* elseClause) noexcept
    : DelphiStatementSyntax{SyntaxKind::CaseStatement},
      _pCaseKeyword{caseKeyword},
      _pSelectorExpression{selectorExpression},
      _pOfKeyword{ofKeyword},
      _pCaseItems{caseItems},
      _pEndKeyword{endKeyword},
      _pSemiColonToken{semiColonToken},
      _pElseClause{elseClause}
{}

SyntaxVariant DelphiCaseStatementSyntax::child(pg_size index) const
{
    switch (childCount())
    {
        case 6:
        {
            switch (index)
            {
                case 0: return SyntaxVariant::asToken(_pCaseKeyword);
                case 1: return SyntaxVariant::asNode(_pSelectorExpression);
                case 2: return SyntaxVariant::asToken(_pOfKeyword);
                case 3: return SyntaxVariant::asList(_pCaseItems);
                case 4: return SyntaxVariant::asToken(_pEndKeyword);
                case 5: return SyntaxVariant::asToken(_pSemiColonToken);
            }
        }
        case 7:
        {
            switch (index)
            {
                case 0: return SyntaxVariant::asToken(_pCaseKeyword);
                case 1: return SyntaxVariant::asNode(_pSelectorExpression);
                case 2: return SyntaxVariant::asToken(_pOfKeyword);
                case 3: return SyntaxVariant::asList(_pCaseItems);
                case 4: return SyntaxVariant::asNode(_pElseClause);
                case 5: return SyntaxVariant::asToken(_pEndKeyword);
                case 6: return SyntaxVariant::asToken(_pSemiColonToken);
            }
        }
    }

    throw std::out_of_range{"index out of range"};
}

DelphiCaseStatementSyntax* DelphiCaseStatementSyntax::create(SyntaxFactory& syntaxFactory,
                                                             ISyntaxToken* caseKeyword,
                                                             DelphiExpressionSyntax* selectorExpression,
                                                             ISyntaxToken* ofKeyword,
                                                             DelphiCaseItemListSyntax* caseItems,
                                                             ISyntaxToken* endKeyword,
                                                             ISyntaxToken* semiColonToken,
                                                             DelphiCaseElseClauseSyntax* elseClause) noexcept
{
    assert(caseKeyword != nullptr);
    assert(caseKeyword->syntaxKind() == SyntaxKind::CaseKeyword);
    assert(selectorExpression != nullptr);
    assert(ofKeyword != nullptr);
    assert(ofKeyword->syntaxKind() == SyntaxKind::OfKeyword);
    assert(caseItems != nullptr);
    assert(endKeyword != nullptr);
    assert(endKeyword->syntaxKind() == SyntaxKind::EndKeyword);
    assert(semiColonToken != nullptr);
    assert(semiColonToken->syntaxKind() == SyntaxKind::SemiColonToken);

    auto ptrCaseStatementSyntax = std::make_unique<DelphiCaseStatementSyntax>(caseKeyword, selectorExpression, ofKeyword,
                                                                              caseItems, endKeyword, semiColonToken, elseClause);

    return static_cast<DelphiCaseStatementSyntax*>(syntaxFactory.addSyntaxNode(std::move(ptrCaseStatementSyntax)));
}

} // end namespace polyglot::Delphi::Syntax
