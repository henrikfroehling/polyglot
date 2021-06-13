#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIEXITSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIEXITSTATEMENTSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Expressions/DelphiParenthesizedExpressionSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiExitStatementSyntax : public DelphiStatementSyntax
{
public:
    explicit DelphiExitStatementSyntax(Core::Syntax::ISyntaxToken* exitKeyword,
                                       Core::Syntax::ISyntaxToken* semiColonToken,
                                       DelphiParenthesizedExpressionSyntax* expression = nullptr) noexcept;

    virtual ~DelphiExitStatementSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* exitKeyword() const noexcept { return _pExitKeyword; }
    inline DelphiParenthesizedExpressionSyntax* expression() const noexcept { return _pExpression; }
    inline Core::Syntax::ISyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }

    inline pg_size childCount() const noexcept override final { return _pExpression != nullptr ? 3 : 2; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pExitKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pSemiColonToken); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiExitStatementSyntax"; }

    inline bool isExitStatement() const noexcept override final { return true; }

    static DelphiExitStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                             Core::Syntax::ISyntaxToken* exitKeyword,
                                             Core::Syntax::ISyntaxToken* semiColonToken,
                                             DelphiParenthesizedExpressionSyntax* expression = nullptr) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pExitKeyword;
    Core::Syntax::ISyntaxToken* _pSemiColonToken;
    DelphiParenthesizedExpressionSyntax* _pExpression; // optional
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIEXITSTATEMENTSYNTAX_H
