#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITINTERFACESECTIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITINTERFACESECTIONSYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiUsesClauseSyntax;
class LanguageSyntaxToken;

class DelphiUnitInterfaceSectionSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitInterfaceSectionSyntax(LanguageSyntaxToken* interfaceKeyword) noexcept;
    virtual ~DelphiUnitInterfaceSectionSyntax() noexcept = default;
    virtual DelphiUsesClauseSyntax* uses() const noexcept { return _pUses; }
    virtual void setUses(DelphiUsesClauseSyntax* uses) noexcept { _pUses = uses; }

private:
    LanguageSyntaxToken* _pInterfaceKeyword;
    DelphiUsesClauseSyntax* _pUses; // optional
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITINTERFACESECTIONSYNTAX_H
