#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiUsesClauseSyntax;
class SyntaxToken;

class DelphiUnitImplementationSectionSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitImplementationSectionSyntax(SyntaxToken* implementationKeyword) noexcept;
    virtual ~DelphiUnitImplementationSectionSyntax() noexcept = default;
    virtual DelphiUsesClauseSyntax* uses() const noexcept { return _pUses; }
    virtual void setUses(DelphiUsesClauseSyntax* uses) noexcept { _pUses = uses; }

private:
    SyntaxToken* _pImplementationKeyword;
    DelphiUsesClauseSyntax* _pUses; // optional
};

} // end namespace polyglot::CodeAnalysis

#endif // #ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H
