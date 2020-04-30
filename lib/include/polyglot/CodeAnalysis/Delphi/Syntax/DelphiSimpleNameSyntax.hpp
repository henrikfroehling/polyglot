#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISIMPLENAMESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISIMPLENAMESYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiNameSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiSimpleNameSyntax : public DelphiNameSyntax
{
public:
    virtual ~DelphiSimpleNameSyntax() noexcept = default;
    inline SyntaxToken identifier() const noexcept { return _identifier; }

protected:
    explicit DelphiSimpleNameSyntax(SyntaxKind syntaxKind,
                                    SyntaxToken identifier) noexcept;

protected:
    SyntaxToken _identifier;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHISIMPLENAMESYNTAX_H
