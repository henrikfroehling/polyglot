#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPROGRAMMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPROGRAMMODULESYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/DelphiCompilationUnitSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiProgramHeadSyntax;
class DelphiUsesClauseSyntax;
class ISyntaxNode;
class ISyntaxToken;
class SyntaxFactory;

class DelphiProgramModuleSyntax : public DelphiCompilationUnitSyntax
{
public:
    explicit DelphiProgramModuleSyntax(DelphiProgramHeadSyntax* head,
                                       DelphiUsesClauseSyntax* uses,
                                       ISyntaxToken* EOFToken) noexcept;

    virtual ~DelphiProgramModuleSyntax() noexcept = default;
    inline bool isProgramModule() const noexcept override { return true; }
    inline DelphiProgramHeadSyntax* head() const noexcept { return _pHead; }
    inline DelphiUsesClauseSyntax* uses() const noexcept { return _pUses; }
    inline pg_size childCount() const noexcept override { return 2; }
    ISyntaxNode* child(pg_size index) const override;

    static DelphiProgramModuleSyntax* create(SyntaxFactory& syntaxFactory,
                                             DelphiProgramHeadSyntax* head,
                                             DelphiUsesClauseSyntax* uses,
                                             ISyntaxToken* EOFToken) noexcept;

    static DelphiProgramModuleSyntax* create(SyntaxFactory& syntaxFactory) noexcept;

private:
    DelphiProgramHeadSyntax* _pHead;
    DelphiUsesClauseSyntax* _pUses;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPROGRAMMODULESYNTAX_H
