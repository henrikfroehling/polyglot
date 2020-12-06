#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITINTERFACESECTIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITINTERFACESECTIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiUnitInterfaceSectionSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitInterfaceSectionSyntax(Ptr<SyntaxToken> interfaceKeyword) noexcept;
    virtual ~DelphiUnitInterfaceSectionSyntax() noexcept = default;
    virtual const Ptr<DelphiUsesClauseSyntax> uses() const noexcept { return _ptrUses; }
    virtual void setUses(Ptr<DelphiUsesClauseSyntax> uses) noexcept { _ptrUses = uses; }

private:
    Ptr<SyntaxToken> _ptrInterfaceKeyword;
    Ptr<DelphiUsesClauseSyntax> _ptrUses; // optional
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITINTERFACESECTIONSYNTAX_H
