#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITINTERFACESECTIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITINTERFACESECTIONSYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Tokens/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiSyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiUnitInterfaceSectionSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitInterfaceSectionSyntax(SyntaxTokenPtr interfaceKeyword) noexcept;
    virtual ~DelphiUnitInterfaceSectionSyntax() noexcept = default;
    virtual const DelphiUsesClauseSyntaxPtr& uses() const noexcept { return _ptrUses; }
    virtual void setUses(DelphiUsesClauseSyntaxPtr uses) noexcept { _ptrUses = std::move(uses); }

private:
    SyntaxTokenPtr _ptrInterfaceKeyword;
    DelphiUsesClauseSyntaxPtr _ptrUses; // optional
};

using DelphiUnitInterfaceSectionSyntaxPtr = std::shared_ptr<DelphiUnitInterfaceSectionSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITINTERFACESECTIONSYNTAX_H
