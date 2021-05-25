#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHICASESTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHICASESTATEMENTSYNTAX_H

#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiStatementSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiCaseStatementSyntax : public DelphiStatementSyntax
{
public:
    DelphiCaseStatementSyntax() noexcept;
    virtual ~DelphiCaseStatementSyntax() noexcept {}
    inline virtual pg_string typeName() const noexcept override { return L"DelphiCaseStatementSyntax"; }

    inline bool isCaseStatement() const noexcept override final { return true; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHICASESTATEMENTSYNTAX_H
