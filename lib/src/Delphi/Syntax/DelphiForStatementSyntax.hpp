#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIFORSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIFORSTATEMENTSYNTAX_H

#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiStatementSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiForStatementSyntax : public DelphiStatementSyntax
{
public:
    DelphiForStatementSyntax() noexcept;
    virtual ~DelphiForStatementSyntax() noexcept {}
    inline virtual pg_string typeName() const noexcept override { return L"DelphiForStatementSyntax"; }

    inline bool isForStatement() const noexcept override final { return true; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIFORSTATEMENTSYNTAX_H
