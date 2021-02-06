#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPACKAGEMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPACKAGEMODULESYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiCompilationUnitSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiPackageContainsClauseSyntax;
class DelphiPackageHeadingSyntax;
class DelphiPackageRequiresClauseSyntax;
class SyntaxFactory;

class DelphiPackageModuleSyntax : public DelphiCompilationUnitSyntax
{
public:
    explicit DelphiPackageModuleSyntax(DelphiPackageHeadingSyntax* heading,
                                       DelphiPackageRequiresClauseSyntax* requiresClause,
                                       DelphiPackageContainsClauseSyntax* containsClause,
                                       LanguageSyntaxToken* EOFToken) noexcept;

    virtual ~DelphiPackageModuleSyntax() noexcept = default;
    inline bool isPackageModule() const noexcept override { return true; }
    inline DelphiPackageHeadingSyntax* heading() const noexcept { return _pHeading; }
    inline DelphiPackageRequiresClauseSyntax* requiresClause() const noexcept { return _pRequiresClause; }
    inline DelphiPackageContainsClauseSyntax* containsClause() const noexcept { return _pContainsClause; }

    static DelphiPackageModuleSyntax* create(SyntaxFactory& syntaxFactory,
                                             DelphiPackageHeadingSyntax* heading,
                                             DelphiPackageRequiresClauseSyntax* requiresClause,
                                             DelphiPackageContainsClauseSyntax* containsClause,
                                             LanguageSyntaxToken* EOFToken) noexcept;

    static DelphiPackageModuleSyntax* create(SyntaxFactory& syntaxFactory) noexcept;

private:
    DelphiPackageHeadingSyntax* _pHeading;
    DelphiPackageRequiresClauseSyntax* _pRequiresClause;
    DelphiPackageContainsClauseSyntax* _pContainsClause;
};

} // polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPACKAGEMODULESYNTAX_H
