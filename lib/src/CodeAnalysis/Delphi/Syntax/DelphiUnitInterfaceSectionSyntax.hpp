#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITINTERFACESECTIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITINTERFACESECTIONSYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiUsesClauseSyntax;
class ISyntaxNode;
class ISyntaxToken;
class SyntaxFactory;

class DelphiUnitInterfaceSectionSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitInterfaceSectionSyntax(ISyntaxToken* interfaceKeyword,
                                              DelphiUsesClauseSyntax* uses = nullptr) noexcept;

    virtual ~DelphiUnitInterfaceSectionSyntax() noexcept = default;
    inline ISyntaxToken* interfaceKeyword() const noexcept { return _pInterfaceKeyword; }
    inline DelphiUsesClauseSyntax* uses() const noexcept { return _pUses; }
    inline pg_size childCount() const noexcept override { return _pUses != nullptr ? 2 : 1; }
    ISyntaxNode* child(pg_size index) const override;

    static DelphiUnitInterfaceSectionSyntax* create(SyntaxFactory& syntaxFactory,
                                                    ISyntaxToken* interfaceKeyword,
                                                    DelphiUsesClauseSyntax* uses = nullptr) noexcept;

private:
    ISyntaxToken* _pInterfaceKeyword;
    DelphiUsesClauseSyntax* _pUses; // optional
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITINTERFACESECTIONSYNTAX_H
