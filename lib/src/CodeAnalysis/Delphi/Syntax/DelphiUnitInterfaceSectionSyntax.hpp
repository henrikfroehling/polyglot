#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITINTERFACESECTIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITINTERFACESECTIONSYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiUsesClauseSyntax;
class LanguageSyntaxToken;
class SyntaxFactory;

class DelphiUnitInterfaceSectionSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitInterfaceSectionSyntax(LanguageSyntaxToken* interfaceKeyword,
                                              DelphiUsesClauseSyntax* uses = nullptr) noexcept;

    virtual ~DelphiUnitInterfaceSectionSyntax() noexcept = default;
    virtual LanguageSyntaxToken* interfaceKeyword() const noexcept { return _pInterfaceKeyword; }
    virtual DelphiUsesClauseSyntax* uses() const noexcept { return _pUses; }

    static DelphiUnitInterfaceSectionSyntax* create(SyntaxFactory& syntaxFactory,
                                                    LanguageSyntaxToken* interfaceKeyword,
                                                    DelphiUsesClauseSyntax* uses = nullptr) noexcept;

private:
    LanguageSyntaxToken* _pInterfaceKeyword;
    DelphiUsesClauseSyntax* _pUses; // optional
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITINTERFACESECTIONSYNTAX_H
