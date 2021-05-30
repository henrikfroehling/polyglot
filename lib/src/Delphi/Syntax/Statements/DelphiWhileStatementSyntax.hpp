#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIWHILESTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIWHILESTATEMENTSYNTAX_H

#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiWhileStatementSyntax : public DelphiStatementSyntax
{
public:
    DelphiWhileStatementSyntax() noexcept;
    virtual ~DelphiWhileStatementSyntax() noexcept {}
    inline virtual pg_string typeName() const noexcept override { return L"DelphiWhileStatementSyntax"; }

    inline bool isWhileStatement() const noexcept override final { return true; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIWHILESTATEMENTSYNTAX_H
