#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxList.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxList;
class ISyntaxNode;
class ISyntaxToken;
class SyntaxFactory;

class DelphiUsesClauseSyntax : public DelphiSyntaxList
{
public:
    explicit DelphiUsesClauseSyntax(ISyntaxToken* usesKeyword,
                                    ISyntaxList* unitReferences,
                                    ISyntaxToken* semiColonToken) noexcept;

    virtual ~DelphiUsesClauseSyntax() noexcept = default;

    inline ISyntaxToken* usesKeyword() const noexcept { return _pUsesKeyword; }
    inline ISyntaxList* unitReferences() const noexcept { return _pUnitReferences; }
    inline ISyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }
    inline pg_size childCount() const noexcept override { return 3; }
    ISyntaxNode* child(pg_size index) const override;

    static DelphiUsesClauseSyntax* create(SyntaxFactory& syntaxFactory,
                                          ISyntaxToken* usesKeyword,
                                          ISyntaxList* unitReferences,
                                          ISyntaxToken* semiColonToken) noexcept;

private:
    ISyntaxToken* _pUsesKeyword;
    ISyntaxList* _pUnitReferences;
    ISyntaxToken* _pSemiColonToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H
