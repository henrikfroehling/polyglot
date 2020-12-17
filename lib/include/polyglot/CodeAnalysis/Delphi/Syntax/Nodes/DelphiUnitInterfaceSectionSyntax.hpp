#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITINTERFACESECTIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITINTERFACESECTIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiUsesClauseSyntax;
class SyntaxToken;

class POLYGLOT_API DelphiUnitInterfaceSectionSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitInterfaceSectionSyntax(SyntaxToken* interfaceKeyword) noexcept;
    virtual ~DelphiUnitInterfaceSectionSyntax() noexcept = default;
    virtual DelphiUsesClauseSyntax* uses() const noexcept { return _ptrUses; }
    virtual void setUses(DelphiUsesClauseSyntax* uses) noexcept { _ptrUses = uses; }

private:
    SyntaxToken* _ptrInterfaceKeyword;
    DelphiUsesClauseSyntax* _ptrUses; // optional
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITINTERFACESECTIONSYNTAX_H
