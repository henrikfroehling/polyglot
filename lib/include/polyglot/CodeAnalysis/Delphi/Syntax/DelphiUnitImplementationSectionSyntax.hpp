#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUsesClauseSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiUnitImplementationSectionSyntax : public DelphiSyntaxNode
{
public:
    DelphiUnitImplementationSectionSyntax() noexcept;
    virtual ~DelphiUnitImplementationSectionSyntax() noexcept = default;
    virtual const DelphiUsesClauseSyntaxPtr& uses() const noexcept { return _ptrUses; }
    virtual void setUses(DelphiUsesClauseSyntaxPtr uses) noexcept { _ptrUses = uses; }

private:
    DelphiUsesClauseSyntaxPtr _ptrUses;
};

using DelphiUnitImplementationSectionSyntaxPtr = std::shared_ptr<DelphiUnitImplementationSectionSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // #ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H
