#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIWITHSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIWITHSTATEMENTSYNTAX_H

#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiStatementSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiWithStatementSyntax : public DelphiStatementSyntax
{
public:
    DelphiWithStatementSyntax() noexcept;
    virtual ~DelphiWithStatementSyntax() noexcept {}
    inline virtual pg_string typeName() const noexcept override { return L"DelphiWithStatementSyntax"; }

    inline bool isWithStatement() const noexcept override final { return true; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIWITHSTATEMENTSYNTAX_H
