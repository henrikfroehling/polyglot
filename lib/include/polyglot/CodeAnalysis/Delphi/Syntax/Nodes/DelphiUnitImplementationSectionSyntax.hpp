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
    explicit DelphiUnitImplementationSectionSyntax(Ptr<SyntaxToken> implementationKeyword) noexcept;
    virtual ~DelphiUnitImplementationSectionSyntax() noexcept = default;
    virtual const Ptr<DelphiUsesClauseSyntax> uses() const noexcept { return _ptrUses; }
    virtual void setUses(Ptr<DelphiUsesClauseSyntax> uses) noexcept { _ptrUses = uses; }

private:
    Ptr<SyntaxToken> _ptrImplementationKeyword;
    Ptr<DelphiUsesClauseSyntax> _ptrUses; // optional
};

} // end namespace polyglot::CodeAnalysis

#endif // #ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H
