#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxList;
class LanguageSyntaxToken;
class SyntaxFactory;

class DelphiUsesClauseSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUsesClauseSyntax(LanguageSyntaxToken* usesKeyword,
                                    LanguageSyntaxList* unitReferences,
                                    LanguageSyntaxToken* semiColonToken) noexcept;

    virtual ~DelphiUsesClauseSyntax() noexcept = default;

    inline LanguageSyntaxToken* usesKeyword() const noexcept { return _pUsesKeyword; }
    inline LanguageSyntaxList* unitReferences() const noexcept { return _pUnitReferences; }
    inline LanguageSyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }

    static DelphiUsesClauseSyntax* create(SyntaxFactory& syntaxFactory,
                                          LanguageSyntaxToken* usesKeyword,
                                          LanguageSyntaxList* unitReferences,
                                          LanguageSyntaxToken* semiColonToken) noexcept;

private:
    LanguageSyntaxToken* _pUsesKeyword;
    LanguageSyntaxList* _pUnitReferences;
    LanguageSyntaxToken* _pSemiColonToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H
