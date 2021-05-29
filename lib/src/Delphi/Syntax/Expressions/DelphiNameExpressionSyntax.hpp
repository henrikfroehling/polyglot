#ifndef POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHINAMEEXPRESSIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHINAMEEXPRESSIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Expressions/DelphiTypeExpressionSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiNameExpressionSyntax : public DelphiTypeExpressionSyntax
{
public:
    explicit DelphiNameExpressionSyntax(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiNameExpressionSyntax() noexcept {}

    inline virtual pg_string typeName() const noexcept override { return L"DelphiNameExpressionSyntax"; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHINAMEEXPRESSIONSYNTAX_H
