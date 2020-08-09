#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHITYPESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHITYPESYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiExpressionSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiTypeSyntax : public DelphiExpressionSyntax
{
public:
    virtual ~DelphiTypeSyntax() noexcept = default;

protected:
    explicit DelphiTypeSyntax(SyntaxKind syntaxKind) noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHITYPESYNTAX_H
