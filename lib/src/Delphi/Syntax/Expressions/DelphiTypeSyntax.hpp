#ifndef POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHITYPESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHITYPESYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Expressions/DelphiExpressionSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiTypeSyntax : public DelphiExpressionSyntax
{
public:
    explicit DelphiTypeSyntax(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiTypeSyntax() noexcept {}

    inline virtual pg_string typeName() const noexcept override { return L"DelphiTypeSyntax"; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHITYPESYNTAX_H
