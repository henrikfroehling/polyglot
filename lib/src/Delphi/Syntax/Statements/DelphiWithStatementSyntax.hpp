#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIWITHSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIWITHSTATEMENTSYNTAX_H

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

class DelphiExpressionSyntax;

class DelphiWithStatementSyntax : public DelphiStatementSyntax
{
public:
    explicit DelphiWithStatementSyntax(Core::Syntax::ISyntaxToken* withKeyword,
                                       DelphiExpressionSyntax* expression,
                                       Core::Syntax::ISyntaxToken* doKeyword,
                                       DelphiStatementSyntax* statement) noexcept;

    virtual ~DelphiWithStatementSyntax() noexcept {}

    inline Core::Syntax::ISyntaxToken* withKeyword() const noexcept { return _pWithKeyword; }
    inline DelphiExpressionSyntax* expression() const noexcept { return _pExpression; }
    inline Core::Syntax::ISyntaxToken* doKeyword() const noexcept { return _pDoKeyword; }
    inline DelphiStatementSyntax* statement() const noexcept { return _pStatement; }

    inline pg_size childCount() const noexcept override final { return 4; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline Core::Syntax::SyntaxVariant first() const noexcept override final { return Core::Syntax::SyntaxVariant::asToken(_pWithKeyword); }
    inline Core::Syntax::SyntaxVariant last() const noexcept override final { return Core::Syntax::SyntaxVariant::asNode(_pStatement); }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiWithStatementSyntax"; }

    inline bool isWithStatement() const noexcept override final { return true; }

    static DelphiWithStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                             Core::Syntax::ISyntaxToken* withKeyword,
                                             DelphiExpressionSyntax* expression,
                                             Core::Syntax::ISyntaxToken* doKeyword,
                                             DelphiStatementSyntax* statement) noexcept;

private:
    Core::Syntax::ISyntaxToken* _pWithKeyword;
    DelphiExpressionSyntax* _pExpression;
    Core::Syntax::ISyntaxToken* _pDoKeyword;
    DelphiStatementSyntax* _pStatement;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIWITHSTATEMENTSYNTAX_H
