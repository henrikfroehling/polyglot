#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_TRYEXCEPTSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_TRYEXCEPTSTATEMENTSYNTAX_H

#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Statements/DelphiTryStatementSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiExceptClauseSyntax;
class DelphiStatementListSyntax;

class DelphiTryExceptStatementSyntax : public DelphiTryStatementSyntax
{
public:
    explicit DelphiTryExceptStatementSyntax(Core::Syntax::ISyntaxToken* tryKeyword,
                                            DelphiStatementListSyntax* statements,
                                            DelphiExceptClauseSyntax* exceptClause,
                                            Core::Syntax::ISyntaxToken* endKeyword,
                                            Core::Syntax::ISyntaxToken* semiColonToken) noexcept;

    virtual ~DelphiTryExceptStatementSyntax() noexcept {}

    inline DelphiExceptClauseSyntax* exceptClause() const noexcept { return _pExceptClause; }

    inline virtual pg_string typeName() const noexcept override { return L"DelphiTryExceptStatementSyntax"; }
    inline bool isTryExceptStatement() const noexcept override final { return true; }

    static DelphiTryExceptStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                  Core::Syntax::ISyntaxToken* tryKeyword,
                                                  DelphiStatementListSyntax* statements,
                                                  DelphiExceptClauseSyntax* exceptClause,
                                                  Core::Syntax::ISyntaxToken* endKeyword,
                                                  Core::Syntax::ISyntaxToken* semiColonToken) noexcept;

private:
    DelphiExceptClauseSyntax* _pExceptClause;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_TRYEXCEPTSTATEMENTSYNTAX_H
