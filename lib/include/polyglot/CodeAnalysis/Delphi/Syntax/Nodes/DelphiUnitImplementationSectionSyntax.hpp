#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiUnitImplementationSectionSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitImplementationSectionSyntax(SharedPtr<SyntaxToken> implementationKeyword) noexcept;
    virtual ~DelphiUnitImplementationSectionSyntax() noexcept = default;
    virtual const SharedPtr<DelphiUsesClauseSyntax>& uses() const noexcept { return _ptrUses; }
    virtual void setUses(SharedPtr<DelphiUsesClauseSyntax> uses) noexcept { _ptrUses = std::move(uses); }

private:
    SharedPtr<SyntaxToken> _ptrImplementationKeyword;
    SharedPtr<DelphiUsesClauseSyntax> _ptrUses; // optional
};

} // end namespace polyglot::CodeAnalysis

#endif // #ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H
