#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITINTERFACESECTIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITINTERFACESECTIONSYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiUsesClauseSyntax;
class LanguageSyntaxNode;
class LanguageSyntaxToken;
class SyntaxFactory;

class DelphiUnitInterfaceSectionSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitInterfaceSectionSyntax(LanguageSyntaxToken* interfaceKeyword,
                                              DelphiUsesClauseSyntax* uses = nullptr) noexcept;

    virtual ~DelphiUnitInterfaceSectionSyntax() noexcept = default;
    inline LanguageSyntaxToken* interfaceKeyword() const noexcept { return _pInterfaceKeyword; }
    inline DelphiUsesClauseSyntax* uses() const noexcept { return _pUses; }
    LanguageSyntaxNode* child(pg_size index) const override;
    inline pg_size childCount() const noexcept override { return _pUses != nullptr ? 2 : 1; }

    static DelphiUnitInterfaceSectionSyntax* create(SyntaxFactory& syntaxFactory,
                                                    LanguageSyntaxToken* interfaceKeyword,
                                                    DelphiUsesClauseSyntax* uses = nullptr) noexcept;

private:
    LanguageSyntaxToken* _pInterfaceKeyword;
    DelphiUsesClauseSyntax* _pUses; // optional
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITINTERFACESECTIONSYNTAX_H
