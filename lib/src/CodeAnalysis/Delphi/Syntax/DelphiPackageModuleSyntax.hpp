#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPACKAGEMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPACKAGEMODULESYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/DelphiCompilationUnitSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiPackageContainsClauseSyntax;
class DelphiPackageHeadSyntax;
class DelphiPackageRequiresClauseSyntax;
class LanguageSyntaxNode;
class SyntaxFactory;

class DelphiPackageModuleSyntax : public DelphiCompilationUnitSyntax
{
public:
    explicit DelphiPackageModuleSyntax(DelphiPackageHeadSyntax* head,
                                       DelphiPackageRequiresClauseSyntax* requiresClause,
                                       DelphiPackageContainsClauseSyntax* containsClause,
                                       LanguageSyntaxToken* EOFToken) noexcept;

    virtual ~DelphiPackageModuleSyntax() noexcept = default;
    inline bool isPackageModule() const noexcept override { return true; }
    inline DelphiPackageHeadSyntax* head() const noexcept { return _pHead; }
    inline DelphiPackageRequiresClauseSyntax* requiresClause() const noexcept { return _pRequiresClause; }
    inline DelphiPackageContainsClauseSyntax* containsClause() const noexcept { return _pContainsClause; }
    LanguageSyntaxNode* child(pg_size index) const override;
    inline pg_size childCount() const noexcept override { return 3; }

    static DelphiPackageModuleSyntax* create(SyntaxFactory& syntaxFactory,
                                             DelphiPackageHeadSyntax* head,
                                             DelphiPackageRequiresClauseSyntax* requiresClause,
                                             DelphiPackageContainsClauseSyntax* containsClause,
                                             LanguageSyntaxToken* EOFToken) noexcept;

    static DelphiPackageModuleSyntax* create(SyntaxFactory& syntaxFactory) noexcept;

private:
    DelphiPackageHeadSyntax* _pHead;
    DelphiPackageRequiresClauseSyntax* _pRequiresClause;
    DelphiPackageContainsClauseSyntax* _pContainsClause;
};

} // polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPACKAGEMODULESYNTAX_H
