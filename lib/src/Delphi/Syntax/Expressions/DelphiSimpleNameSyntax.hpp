#ifndef POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHISIMPLENAMESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHISIMPLENAMESYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Expressions/DelphiNameSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiSimpleNameSyntax : public DelphiNameSyntax
{
public:
    explicit DelphiSimpleNameSyntax(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiSimpleNameSyntax() noexcept {}

    inline virtual pg_string typeName() const noexcept override { return L"DelphiSimpleNameSyntax"; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHISIMPLENAMESYNTAX_H
