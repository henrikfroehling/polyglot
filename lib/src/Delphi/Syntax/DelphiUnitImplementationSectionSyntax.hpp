#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H

#include "DelphiSyntaxNode.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiUsesClauseSyntax;
class ISyntaxNode;
class ISyntaxToken;
class SyntaxFactory;

class DelphiUnitImplementationSectionSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitImplementationSectionSyntax(ISyntaxToken* implementationKeyword,
                                                   DelphiUsesClauseSyntax* uses = nullptr) noexcept;

    virtual ~DelphiUnitImplementationSectionSyntax() noexcept = default;
    inline ISyntaxToken* implementationKeyword() const noexcept { return _pImplementationKeyword; }
    inline DelphiUsesClauseSyntax* uses() const noexcept { return _pUses; }
    inline pg_size childCount() const noexcept override { return _pUses != nullptr ? 2 : 1; }
    ISyntaxNode* child(pg_size index) const override;

    static DelphiUnitImplementationSectionSyntax* create(SyntaxFactory& syntaxFactory,
                                                         ISyntaxToken* implementationKeyword,
                                                         DelphiUsesClauseSyntax* uses = nullptr) noexcept;

private:
    ISyntaxToken* _pImplementationKeyword;
    DelphiUsesClauseSyntax* _pUses; // optional
};

} // end namespace polyglot::Delphi::Syntax

#endif // #ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H
