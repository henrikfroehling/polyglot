#ifndef POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIEXPRESSIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIEXPRESSIONSYNTAX_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/LanguageKind.hpp"
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiExpressionSyntax : public Core::Syntax::ExpressionSyntax
{
public:
    explicit DelphiExpressionSyntax(Core::Syntax::SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiExpressionSyntax() noexcept {}
    inline Core::LanguageKind languageKind() const noexcept override final { return Core::LanguageKind::Delphi; }
    inline virtual pg_string typeName() const noexcept override { return L"DelphiExpressionSyntax"; }
};

} // end namespace polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_EXPRESSIONS_DELPHIEXPRESSIONSYNTAX_H
