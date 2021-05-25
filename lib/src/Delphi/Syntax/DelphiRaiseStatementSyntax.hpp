#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIRAISESTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIRAISESTATEMENTSYNTAX_H

#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiStatementSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiRaiseStatementSyntax : public DelphiStatementSyntax
{
public:
    DelphiRaiseStatementSyntax() noexcept;
    virtual ~DelphiRaiseStatementSyntax() noexcept {}
    inline virtual pg_string typeName() const noexcept override { return L"DelphiRaiseStatementSyntax"; }

    inline bool isRaiseStatement() const noexcept override final { return true; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIRAISESTATEMENTSYNTAX_H
