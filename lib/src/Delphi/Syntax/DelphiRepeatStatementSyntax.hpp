#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIREPEATSTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIREPEATSTATEMENTSYNTAX_H

#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiStatementSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiRepeatStatementSyntax : public DelphiStatementSyntax
{
public:
    DelphiRepeatStatementSyntax() noexcept;
    virtual ~DelphiRepeatStatementSyntax() noexcept {}
    inline virtual pg_string typeName() const noexcept override { return L"DelphiRepeatStatementSyntax"; }

    inline bool isRepeatStatement() const noexcept override final { return true; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIREPEATSTATEMENTSYNTAX_H
