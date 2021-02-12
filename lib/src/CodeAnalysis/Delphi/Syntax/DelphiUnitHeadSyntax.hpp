#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITHEADSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITHEADSYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxNode;
class LanguageSyntaxToken;
class NameExpressionSyntax;
class SyntaxFactory;

class DelphiUnitHeadSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitHeadSyntax(LanguageSyntaxToken* unitKeyword,
                                  NameExpressionSyntax* name,
                                  LanguageSyntaxToken* semiColonToken,
                                  LanguageSyntaxToken* inKeyword = nullptr,
                                  LanguageSyntaxToken* filename = nullptr) noexcept;

    virtual ~DelphiUnitHeadSyntax() noexcept = default;
    inline LanguageSyntaxToken* unitKeyword() const noexcept { return _pUnitKeyword; }
    inline NameExpressionSyntax* name() const noexcept { return _pName; }
    inline LanguageSyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }
    inline LanguageSyntaxToken* inKeyword() const noexcept { return _pInKeyword; }
    inline LanguageSyntaxToken* filename() const noexcept { return _pFilename; }
    LanguageSyntaxNode* child(pg_size index) const override;
    inline pg_size childCount() const noexcept override { return _pFilename != nullptr ? 5 : 3; }

    static DelphiUnitHeadSyntax* create(SyntaxFactory& syntaxFactory,
                                        LanguageSyntaxToken* unitKeyword,
                                        NameExpressionSyntax* name,
                                        LanguageSyntaxToken* semiColonToken,
                                        LanguageSyntaxToken* inKeyword = nullptr,
                                        LanguageSyntaxToken* filename = nullptr) noexcept;

private:
    LanguageSyntaxToken* _pUnitKeyword;
    NameExpressionSyntax* _pName;
    LanguageSyntaxToken* _pSemiColonToken;
    LanguageSyntaxToken* _pInKeyword; // optional
    LanguageSyntaxToken* _pFilename; // optional
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITHEADSYNTAX_H
