#ifndef POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGEMODULESYNTAX_H
#define POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGEMODULESYNTAX_H

#include "DelphiCompilationUnitSyntax.hpp"

namespace polyglot::Delphi::Syntax
{

class DelphiPackageContainsClauseSyntax;
class DelphiPackageHeadSyntax;
class DelphiPackageRequiresClauseSyntax;
class ISyntaxNode;
class ISyntaxToken;
class SyntaxFactory;

class DelphiPackageModuleSyntax : public DelphiCompilationUnitSyntax
{
public:
    explicit DelphiPackageModuleSyntax(DelphiPackageHeadSyntax* head,
                                       DelphiPackageRequiresClauseSyntax* requiresClause,
                                       DelphiPackageContainsClauseSyntax* containsClause,
                                       ISyntaxToken* EOFToken) noexcept;

    virtual ~DelphiPackageModuleSyntax() noexcept = default;
    inline bool isPackageModule() const noexcept override { return true; }
    inline DelphiPackageHeadSyntax* head() const noexcept { return _pHead; }
    inline DelphiPackageRequiresClauseSyntax* requiresClause() const noexcept { return _pRequiresClause; }
    inline DelphiPackageContainsClauseSyntax* containsClause() const noexcept { return _pContainsClause; }
    inline pg_size childCount() const noexcept override { return 3; }
    ISyntaxNode* child(pg_size index) const override;

    static DelphiPackageModuleSyntax* create(SyntaxFactory& syntaxFactory,
                                             DelphiPackageHeadSyntax* head,
                                             DelphiPackageRequiresClauseSyntax* requiresClause,
                                             DelphiPackageContainsClauseSyntax* containsClause,
                                             ISyntaxToken* EOFToken) noexcept;

    static DelphiPackageModuleSyntax* create(SyntaxFactory& syntaxFactory) noexcept;

private:
    DelphiPackageHeadSyntax* _pHead;
    DelphiPackageRequiresClauseSyntax* _pRequiresClause;
    DelphiPackageContainsClauseSyntax* _pContainsClause;
};

} // polyglot::Delphi::Syntax

#endif // POLYGLOT_DELPHI_SYNTAX_DELPHIPACKAGEMODULESYNTAX_H
