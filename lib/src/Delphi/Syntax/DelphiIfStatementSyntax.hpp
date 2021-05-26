#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIIFSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIIFSTATEMENTSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiStatementSyntax.hpp"
#include "Delphi/Syntax/DelphiStatementListSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiExpressionSyntax;

class DelphiIfStatementSyntax : public DelphiStatementSyntax
{
public:
    explicit DelphiIfStatementSyntax(Core::Syntax::ISyntaxToken* ifKeyword,
                                     DelphiExpressionSyntax* conditionExpression,
                                     Core::Syntax::ISyntaxToken* thenKeyword,
                                     DelphiStatementListSyntax* statementList) noexcept;

    virtual ~DelphiIfStatementSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* ifKeyword() const noexcept { return _pIfKeyword; }
    inline DelphiExpressionSyntax* conditionExpression() const noexcept { return _pConditionExpression; }
    inline Core::Syntax::ISyntaxToken* thenKeyword() const noexcept { return _pThenKeyword; }
    inline DelphiStatementListSyntax* statementList() const noexcept { return _pStatementList; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pIfKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asList(_pStatementList); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiIfStatementSyntax"; }

    inline bool isIfStatement() const noexcept override final { return true; }

    static DelphiIfStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                           Core::Syntax::ISyntaxToken* ifKeyword,
                                           DelphiExpressionSyntax* conditionExpression,
                                           Core::Syntax::ISyntaxToken* thenKeyword,
                                           DelphiStatementListSyntax* statementList) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pIfKeyword;
    DelphiExpressionSyntax* _pConditionExpression;
    Core::Syntax::ISyntaxToken* _pThenKeyword;
    DelphiStatementListSyntax* _pStatementList;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIIFSTATEMENTSYNTAX_H
