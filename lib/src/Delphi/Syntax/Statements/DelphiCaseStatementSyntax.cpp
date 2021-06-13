#include "Delphi/Syntax/Statements/DelphiCaseStatementSyntax.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"

namespace polyglot::Delphi::Syntax
{

using Core::Syntax::SyntaxKind;

DelphiCaseStatementSyntax::DelphiCaseStatementSyntax(Core::Syntax::ISyntaxToken* caseKeyword,
                                                     DelphiExpressionSyntax* selectorExpression,
                                                     Core::Syntax::ISyntaxToken* ofKeyword,
                                                     DelphiCaseItemListSyntax* caseItems,
                                                     Core::Syntax::ISyntaxToken* endKeyword,
                                                     Core::Syntax::ISyntaxToken* semiColonToken,
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

DelphiCaseStatementSyntax* DelphiCaseStatementSyntax::create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                             Core::Syntax::ISyntaxToken* caseKeyword,
                                                             DelphiExpressionSyntax* selectorExpression,
                                                             Core::Syntax::ISyntaxToken* ofKeyword,
                                                             DelphiCaseItemListSyntax* caseItems,
                                                             Core::Syntax::ISyntaxToken* endKeyword,
                                                             Core::Syntax::ISyntaxToken* semiColonToken,
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
