#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHINAMESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHINAMESYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiTypeSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiNameSyntax : public DelphiTypeSyntax
{
public:
    virtual ~DelphiNameSyntax() noexcept = default;

protected:
    explicit DelphiNameSyntax(SyntaxKind syntaxKind) noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHINAMESYNTAX_H
