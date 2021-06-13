#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_FORTOSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_FORTOSTATEMENTSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Statements/DelphiForStatementSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiExpressionSyntax;
class DelphiStatementSyntax;

class DelphiForToStatementSyntax : public DelphiForStatementSyntax
{
public:
    explicit DelphiForToStatementSyntax(Core::Syntax::ISyntaxToken* forKeyword,
                                        DelphiExpressionSyntax* initialValueExpression,
                                        Core::Syntax::ISyntaxToken* toOrDownToKeyword,
                                        DelphiExpressionSyntax* finalValueExpression,
                                        Core::Syntax::ISyntaxToken* doKeyword,
                                        DelphiStatementSyntax* statement) noexcept;

    virtual ~DelphiForToStatementSyntax() noexcept {}

    inline DelphiExpressionSyntax* initialValueExpression() const noexcept { return _pInitialValueExpression; }
    inline Core::Syntax::ISyntaxToken* toOrDownToKeyword() const noexcept { return _pToOrDownToKeyword; }
    inline DelphiExpressionSyntax* finalValueExpression() const noexcept { return _pFinalValueExpression; }

    inline pg_size childCount() const noexcept override final { return 6; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline virtual pg_string typeName() const noexcept override { return L"DelphiForToStatementSyntax"; }
    inline bool isForToStatement() const noexcept override final { return true; }

    static DelphiForToStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                              Core::Syntax::ISyntaxToken* forKeyword,
                                              DelphiExpressionSyntax* initialValueExpression,
                                              Core::Syntax::ISyntaxToken* toOrDownToKeyword,
                                              DelphiExpressionSyntax* finalValueExpression,
                                              Core::Syntax::ISyntaxToken* doKeyword,
                                              DelphiStatementSyntax* statement) noexcept;

private:
    DelphiExpressionSyntax* _pInitialValueExpression;
    Core::Syntax::ISyntaxToken* _pToOrDownToKeyword;
    DelphiExpressionSyntax* _pFinalValueExpression;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_FORTOSTATEMENTSYNTAX_H
