#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIIFSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIIFSTATEMENTSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementSyntax.hpp"
#include "Delphi/Syntax/DelphiElseClauseSyntax.hpp"

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
                                     DelphiStatementSyntax* statement,
                                     DelphiElseClauseSyntax* elseClause = nullptr) noexcept;

    virtual ~DelphiIfStatementSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* ifKeyword() const noexcept { return _pIfKeyword; }
    inline DelphiExpressionSyntax* conditionExpression() const noexcept { return _pConditionExpression; }
    inline Core::Syntax::ISyntaxToken* thenKeyword() const noexcept { return _pThenKeyword; }
    inline DelphiStatementSyntax* statement() const noexcept { return _pStatement; }
    inline DelphiElseClauseSyntax* elseClause() const noexcept { return _pElseClause; }

    inline pg_size childCount() const noexcept override final { return _pElseClause != nullptr ? 5 : 4; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pIfKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final
    {
        if (_pElseClause != nullptr)
            return Core::Syntax::SyntaxVariant::asNode(_pElseClause);

        return Core::Syntax::SyntaxVariant::asNode(_pStatement);
    }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiIfStatementSyntax"; }

    inline bool isIfStatement() const noexcept override final { return true; }

    static DelphiIfStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                           Core::Syntax::ISyntaxToken* ifKeyword,
                                           DelphiExpressionSyntax* conditionExpression,
                                           Core::Syntax::ISyntaxToken* thenKeyword,
                                           DelphiStatementSyntax* statement,
                                           DelphiElseClauseSyntax* elseClause = nullptr) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pIfKeyword;
    DelphiExpressionSyntax* _pConditionExpression;
    Core::Syntax::ISyntaxToken* _pThenKeyword;
    DelphiStatementSyntax* _pStatement;
    DelphiElseClauseSyntax* _pElseClause; // optional
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIIFSTATEMENTSYNTAX_H
