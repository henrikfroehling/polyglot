#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITHEADINGSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITHEADINGSYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;
class NameExpressionSyntax;

class DelphiUnitHeadingSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitHeadingSyntax(LanguageSyntaxToken* unitKeyword,
                                     NameExpressionSyntax* name,
                                     LanguageSyntaxToken* semiColonToken) noexcept;

    virtual ~DelphiUnitHeadingSyntax() noexcept = default;
    LanguageSyntaxToken* unitKeyword() const noexcept { return _pUnitKeyword; }
    NameExpressionSyntax* name() const noexcept { return _pName; }
    LanguageSyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }

    static DelphiUnitHeadingSyntax* create(LanguageSyntaxToken* unitKeyword,
                                           NameExpressionSyntax* name,
                                           LanguageSyntaxToken* semiColonToken) noexcept;

private:
    LanguageSyntaxToken* _pUnitKeyword;
    NameExpressionSyntax* _pName;
    LanguageSyntaxToken* _pSemiColonToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITHEADINGSYNTAX_H
