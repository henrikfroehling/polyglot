#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIEXPRESSIONSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIEXPRESSIONSTATEMENTSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Expressions/DelphiExpressionSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiExpressionStatementSyntax : public DelphiStatementSyntax
{
public:
    explicit DelphiExpressionStatementSyntax(DelphiExpressionSyntax* expression,
                                             Core::Syntax::ISyntaxToken* semiColonToken) noexcept;

    virtual ~DelphiExpressionStatementSyntax() noexcept {}

    inline DelphiExpressionSyntax* expression() const noexcept { return _pExpression; }
    inline Core::Syntax::ISyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asNode(_pExpression); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pSemiColonToken); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiExpressionStatementSyntax"; }

    inline bool isExpressionStatement() const noexcept override final { return true; }

    static DelphiExpressionStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                   DelphiExpressionSyntax* expression,
                                                   Core::Syntax::ISyntaxToken* semiColonToken) noexcept;

private:
    DelphiExpressionSyntax* _pExpression;
    Core::Syntax::ISyntaxToken* _pSemiColonToken;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHISIMPLESTATEMENTSYNTAX_H
