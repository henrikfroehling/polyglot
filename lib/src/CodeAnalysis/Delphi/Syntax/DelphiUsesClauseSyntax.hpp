#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class ISyntaxNode;
class ISyntaxToken;
class SyntaxFactory;
class SyntaxList;

class DelphiUsesClauseSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUsesClauseSyntax(ISyntaxToken* usesKeyword,
                                    SyntaxList* unitReferences,
                                    ISyntaxToken* semiColonToken) noexcept;

    virtual ~DelphiUsesClauseSyntax() noexcept = default;

    inline ISyntaxToken* usesKeyword() const noexcept { return _pUsesKeyword; }
    inline SyntaxList* unitReferences() const noexcept { return _pUnitReferences; }
    inline ISyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }
    inline pg_size childCount() const noexcept override { return 3; }
    ISyntaxNode* child(pg_size index) const override;

    static DelphiUsesClauseSyntax* create(SyntaxFactory& syntaxFactory,
                                          ISyntaxToken* usesKeyword,
                                          SyntaxList* unitReferences,
                                          ISyntaxToken* semiColonToken) noexcept;

private:
    ISyntaxToken* _pUsesKeyword;
    SyntaxList* _pUnitReferences;
    ISyntaxToken* _pSemiColonToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H
