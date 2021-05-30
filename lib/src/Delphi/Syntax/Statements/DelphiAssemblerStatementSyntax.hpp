#ifndef POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIASSEMBLERSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIASSEMBLERSTATEMENTSYNTAX_H

#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiAssemblerStatementSyntax : public DelphiStatementSyntax
{
public:
    DelphiAssemblerStatementSyntax() noexcept;
    virtual ~DelphiAssemblerStatementSyntax() noexcept {}
    inline virtual pg_string typeName() const noexcept override { return L"DelphiAssemblerStatementSyntax"; }

    inline bool isAssemblerStatement() const noexcept override final { return true; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_STATEMENTS_DELPHIASSEMBLERSTATEMENTSYNTAX_H
