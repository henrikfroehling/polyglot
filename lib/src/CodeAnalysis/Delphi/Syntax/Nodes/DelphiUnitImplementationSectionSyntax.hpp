#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/DelphiSyntaxNode.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiUsesClauseSyntax;
class LanguageSyntaxToken;
class SyntaxFactory;

class DelphiUnitImplementationSectionSyntax : public DelphiSyntaxNode
{
public:
    explicit DelphiUnitImplementationSectionSyntax(LanguageSyntaxToken* implementationKeyword,
                                                   DelphiUsesClauseSyntax* uses = nullptr) noexcept;

    virtual ~DelphiUnitImplementationSectionSyntax() noexcept = default;
    virtual LanguageSyntaxToken* implementationKeyword() const noexcept { return _pImplementationKeyword; }
    virtual DelphiUsesClauseSyntax* uses() const noexcept { return _pUses; }

    static DelphiUnitImplementationSectionSyntax* create(SyntaxFactory& syntaxFactory,
                                                         LanguageSyntaxToken* implementationKeyword,
                                                         DelphiUsesClauseSyntax* uses = nullptr) noexcept;

private:
    LanguageSyntaxToken* _pImplementationKeyword;
    DelphiUsesClauseSyntax* _pUses; // optional
};

} // end namespace polyglot::CodeAnalysis

#endif // #ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIUNITIMPLEMENTATIONSECTIONSYNTAX_H
