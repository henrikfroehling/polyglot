#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_TRYFINALLYSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_TRYFINALLYSTATEMENTSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Statements/DelphiTryStatementSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;
class SyntaxFactory;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiFinallyClauseSyntax;
class DelphiStatementListSyntax;

class DelphiTryFinallyStatementSyntax : public DelphiTryStatementSyntax
{
public:
    explicit DelphiTryFinallyStatementSyntax(Core::Syntax::ISyntaxToken* tryKeyword,
                                             DelphiStatementListSyntax* statements,
                                             DelphiFinallyClauseSyntax* finallyClause,
                                             Core::Syntax::ISyntaxToken* endKeyword,
                                             Core::Syntax::ISyntaxToken* semiColonToken) noexcept;

    virtual ~DelphiTryFinallyStatementSyntax() noexcept {}

    inline DelphiFinallyClauseSyntax* finallyClause() const noexcept { return _pFinallyClause; }

    inline pg_size childCount() const noexcept override final { return 5; }
    Core::Syntax::SyntaxVariant child(pg_size index) const override final;

    inline virtual pg_string typeName() const noexcept override { return L"DelphiTryFinallyStatementSyntax"; }
    inline bool isTryFinallyStatement() const noexcept override final { return true; }

    static DelphiTryFinallyStatementSyntax* create(Core::Syntax::SyntaxFactory& syntaxFactory,
                                                   Core::Syntax::ISyntaxToken* tryKeyword,
                                                   DelphiStatementListSyntax* statements,
                                                   DelphiFinallyClauseSyntax* finallyClause,
                                                   Core::Syntax::ISyntaxToken* endKeyword,
                                                   Core::Syntax::ISyntaxToken* semiColonToken) noexcept;

private:
    DelphiFinallyClauseSyntax* _pFinallyClause;
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_TRYFINALLYSTATEMENTSYNTAX_H
