#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHITRYSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHITRYSTATEMENTSYNTAX_H

#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiTryStatementSyntax : public DelphiStatementSyntax
{
public:
    DelphiTryStatementSyntax() noexcept;
    virtual ~DelphiTryStatementSyntax() noexcept {}
    inline virtual pg_string typeName() const noexcept override { return L"DelphiTryStatementSyntax"; }

    inline bool isTryStatement() const noexcept override final { return true; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHITRYSTATEMENTSYNTAX_H
