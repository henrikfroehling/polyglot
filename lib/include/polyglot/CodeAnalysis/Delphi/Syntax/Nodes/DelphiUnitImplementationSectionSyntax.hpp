#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiUsesClauseSyntax;
class SyntaxToken;

class POLYGLOT_API DelphiUnitImplementationSectionSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitImplementationSectionSyntax(SyntaxToken* implementationKeyword) noexcept;
    virtual ~DelphiUnitImplementationSectionSyntax() noexcept = default;
    virtual DelphiUsesClauseSyntax* uses() const noexcept { return _ptrUses; }
    virtual void setUses(DelphiUsesClauseSyntax* uses) noexcept { _ptrUses = uses; }

private:
    SyntaxToken* _ptrImplementationKeyword;
    DelphiUsesClauseSyntax* _ptrUses; // optional
};

} // end namespace polyglot::CodeAnalysis

#endif // #ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H
