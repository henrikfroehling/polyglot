#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIEXPRESSIONSYNTAX_H

#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiExpressionSyntax : public ExpressionSyntax
{
public:
    explicit DelphiExpressionSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiExpressionSyntax() noexcept = default;
    inline LanguageKind languageKind() const noexcept override { return LanguageKind::Delphi; }
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIEXPRESSIONSYNTAX_H
