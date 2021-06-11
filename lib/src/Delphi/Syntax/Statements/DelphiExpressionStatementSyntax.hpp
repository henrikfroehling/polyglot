#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIEXPRESSIONSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIEXPRESSIONSTATEMENTSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiExpressionStatementSyntax : public DelphiStatementSyntax
{
public:
    explicit DelphiExpressionStatementSyntax(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiExpressionStatementSyntax() noexcept {}

    inline virtual pg_string typeName() const noexcept override { return L"DelphiExpressionStatementSyntax"; }

    inline bool isExpressionStatement() const noexcept override final { return true; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHISIMPLESTATEMENTSYNTAX_H
