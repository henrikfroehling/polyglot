#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIEXPRESSIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIEXPRESSIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiExpressionSyntax : public DelphiSyntaxNode
{
public:
    virtual ~DelphiExpressionSyntax() noexcept = default;

protected:
    explicit DelphiExpressionSyntax(SyntaxKind syntaxKind) noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIEXPRESSIONSYNTAX_H
