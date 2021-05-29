#ifndef POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHISIMPLENAMEEXPRESSIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHISIMPLENAMEEXPRESSIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
#include "Delphi/Syntax/Expressions/DelphiNameExpressionSyntax.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxToken;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiSimpleNameExpressionSyntax : public DelphiNameExpressionSyntax
{
public:
    explicit DelphiSimpleNameExpressionSyntax(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiSimpleNameExpressionSyntax() noexcept {}
    virtual Core::Syntax::ISyntaxToken* identifier() const noexcept = 0;

    inline virtual pg_string typeName() const noexcept override { return L"DelphiSimpleNameExpressionSyntax"; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHISIMPLENAMEEXPRESSIONSYNTAX_H
