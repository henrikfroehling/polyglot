#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHISIMPLESTATEMENTSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHISIMPLESTATEMENTSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiStatementSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiSimpleStatementSyntax : public DelphiStatementSyntax
{
public:
    explicit DelphiSimpleStatementSyntax(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiSimpleStatementSyntax() noexcept {}

    inline virtual pg_string typeName() const noexcept override { return L"DelphiSimpleStatementSyntax"; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHISIMPLESTATEMENTSYNTAX_H
