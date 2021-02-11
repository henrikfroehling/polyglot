#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H

#include <vector>
#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"
#include "CodeAnalysis/Delphi/Syntax/DelphiUnitReferenceDeclarationSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;
class SyntaxFactory;

class DelphiUsesClauseSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUsesClauseSyntax(LanguageSyntaxToken* usesKeyword,
                                    std::vector<DelphiUnitReferenceDeclarationSyntax*>&& unitReferences,
                                    LanguageSyntaxToken* semiColonToken) noexcept;

    virtual ~DelphiUsesClauseSyntax() noexcept = default;

    inline LanguageSyntaxToken* usesKeyword() const noexcept { return _pUsesKeyword; }
    inline const std::vector<DelphiUnitReferenceDeclarationSyntax*>& unitReferences() const noexcept { return _unitReferences; }

    inline void addUnitReference(DelphiUnitReferenceDeclarationSyntax* unitReference) noexcept
    {
        _unitReferences.push_back(unitReference);
    }

    inline LanguageSyntaxToken* semiColonToken() const noexcept { return _pSemiColonToken; }

    static DelphiUsesClauseSyntax* create(SyntaxFactory& syntaxFactory,
                                          LanguageSyntaxToken* usesKeyword,
                                          std::vector<DelphiUnitReferenceDeclarationSyntax*>&& unitReferences,
                                          LanguageSyntaxToken* semiColonToken) noexcept;

private:
    LanguageSyntaxToken* _pUsesKeyword;
    std::vector<DelphiUnitReferenceDeclarationSyntax*> _unitReferences;
    LanguageSyntaxToken* _pSemiColonToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUSESCLAUSESYNTAX_H
