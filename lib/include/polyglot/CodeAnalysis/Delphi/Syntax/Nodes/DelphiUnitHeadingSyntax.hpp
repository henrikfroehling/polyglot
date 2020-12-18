#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITHEADINGSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITHEADINGSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class NameExpressionSyntax;
class SyntaxToken;

class POLYGLOT_API DelphiUnitHeadingSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitHeadingSyntax(SyntaxToken* unitKeyword,
                                     NameExpressionSyntax* name,
                                     SyntaxToken* semiColonToken) noexcept;

    virtual ~DelphiUnitHeadingSyntax() noexcept = default;
    SyntaxToken* unitKeyword() const noexcept { return _pUnitKeyword; }
    NameExpressionSyntax* name() const noexcept { return _pName; }
    SyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }

private:
    SyntaxToken* _pUnitKeyword;
    NameExpressionSyntax* _pName;
    SyntaxToken* _pSemiColonToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITHEADINGSYNTAX_H
