#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIQUALIFIEDNAMESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIQUALIFIEDNAMESYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiNameSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSimpleNameSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiQualifiedNameSyntax : public DelphiNameSyntax
{
public:
    explicit DelphiQualifiedNameSyntax(SyntaxKind syntaxKind,
                                       DelphiNameSyntax* left,
                                       SyntaxToken dotToken,
                                       DelphiSimpleNameSyntax* right) noexcept;

    virtual ~DelphiQualifiedNameSyntax() noexcept = default;
    inline DelphiNameSyntax* left() const noexcept { return _left; }
    inline SyntaxToken dotToken() const noexcept { return _dotToken; }
    inline DelphiSimpleNameSyntax* right() const noexcept { return _right; }

private:
    DelphiNameSyntax* _left;
    SyntaxToken _dotToken;
    DelphiSimpleNameSyntax* _right;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIQUALIFIEDNAMESYNTAX_H
