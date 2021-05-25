#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIIFSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIIFSTATEMENTSYNTAX_H

#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiStatementSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiIfStatementSyntax : public DelphiStatementSyntax
{
public:
    DelphiIfStatementSyntax() noexcept;
    virtual ~DelphiIfStatementSyntax() noexcept {}
    inline virtual pg_string typeName() const noexcept override { return L"DelphiIfStatementSyntax"; }

    inline bool isIfStatement() const noexcept override final { return true; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIIFSTATEMENTSYNTAX_H
