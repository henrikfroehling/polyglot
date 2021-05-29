#ifndef POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHITYPEEXPRESSIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHITYPEEXPRESSIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/DelphiExpressionSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiTypeExpressionSyntax : public DelphiExpressionSyntax
{
public:
    explicit DelphiTypeExpressionSyntax(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiTypeExpressionSyntax() noexcept {}

    inline virtual pg_string typeName() const noexcept override { return L"DelphiTypeExpressionSyntax"; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHITYPEEXPRESSIONSYNTAX_H
