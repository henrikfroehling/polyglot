#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHICASESTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHICASESTATEMENTSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiCaseElseClauseSyntax;
class DelphiCaseItemListSyntax;
class DelphiExpressionSyntax;

class DelphiCaseStatementSyntax : public DelphiStatementSyntax
{
public:
    explicit DelphiCaseStatementSyntax(Core::Syntax::ISyntaxToken* caseKeyword,
                                       DelphiExpressionSyntax* selectorExpression,
                                       Core::Syntax::ISyntaxToken* ofKeyword,
                                       DelphiCaseItemListSyntax* caseItems,
                                       Core::Syntax::ISyntaxToken* endKeyword,
                                       Core::Syntax::ISyntaxToken* semiColonToken,
                                       DelphiCaseElseClauseSyntax* elseClause = nullptr) noexcept;

    virtual ~DelphiCaseStatementSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* caseKeyword() const noexcept { return _pCaseKeyword; }
    inline DelphiExpressionSyntax* selectorExpression() const noexcept { return _pSelectorExpression; }
    inline Core::Syntax::ISyntaxToken* ofKeyword() const noexcept { return _pOfKeyword; }
    inline DelphiCaseItemListSyntax* caseItems() const noexcept { return _pCaseItems; }
    inline DelphiCaseElseClauseSyntax* elseClause() const noexcept { return _pElseClause; }
    inline Core::Syntax::ISyntaxToken* endKeyword() const noexcept { return _pEndKeyword; }
    inline Core::Syntax::ISyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pCaseKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pSemiColonToken); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiCaseStatementSyntax"; }

    inline bool isCaseStatement() const noexcept override final { return true; }

    static DelphiCaseStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                             Core::Syntax::ISyntaxToken* caseKeyword,
                                             DelphiExpressionSyntax* selectorExpression,
                                             Core::Syntax::ISyntaxToken* ofKeyword,
                                             DelphiCaseItemListSyntax* caseItems,
                                             Core::Syntax::ISyntaxToken* endKeyword,
                                             Core::Syntax::ISyntaxToken* semiColonToken,
                                             DelphiCaseElseClauseSyntax* elseClause = nullptr) noexcept;

protected:
    Core::Syntax::ISyntaxToken* _pCaseKeyword;
    DelphiExpressionSyntax* _pSelectorExpression;
    Core::Syntax::ISyntaxToken* _pOfKeyword;
    DelphiCaseItemListSyntax* _pCaseItems;
    Core::Syntax::ISyntaxToken* _pEndKeyword;
    Core::Syntax::ISyntaxToken* _pSemiColonToken;
    DelphiCaseElseClauseSyntax* _pElseClause; // optional
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHICASESTATEMENTSYNTAX_H
