#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITHEADSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITHEADSYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;
class NameExpressionSyntax;
class SyntaxFactory;

class DelphiUnitHeadSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitHeadSyntax(LanguageSyntaxToken* unitKeyword,
                                  NameExpressionSyntax* name,
                                  LanguageSyntaxToken* semiColonToken) noexcept;

    virtual ~DelphiUnitHeadSyntax() noexcept = default;
    LanguageSyntaxToken* unitKeyword() const noexcept { return _pUnitKeyword; }
    NameExpressionSyntax* name() const noexcept { return _pName; }
    LanguageSyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }

    static DelphiUnitHeadSyntax* create(SyntaxFactory& syntaxFactory,
                                        LanguageSyntaxToken* unitKeyword,
                                        NameExpressionSyntax* name,
                                        LanguageSyntaxToken* semiColonToken) noexcept;

private:
    LanguageSyntaxToken* _pUnitKeyword;
    NameExpressionSyntax* _pName;
    LanguageSyntaxToken* _pSemiColonToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITHEADSYNTAX_H
