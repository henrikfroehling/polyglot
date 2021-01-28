#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPACKAGEMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPACKAGEMODULESYNTAX_H

#include "CodeAnalysis/Delphi/Syntax/Nodes/DelphiCompilationUnitSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiPackageContainsClauseSyntax;
class DelphiPackageHeadingSyntax;
class DelphiPackageRequiresClauseSyntax;

class DelphiPackageModuleSyntax : public DelphiCompilationUnitSyntax
{
public:
    DelphiPackageModuleSyntax() noexcept;
    virtual ~DelphiPackageModuleSyntax() noexcept = default;
    inline bool isPackageModule() const noexcept override { return true; }
    inline DelphiPackageHeadingSyntax* heading() const noexcept { return _pHeading; }
    void setHeading(DelphiPackageHeadingSyntax* heading) noexcept;
    inline DelphiPackageRequiresClauseSyntax* requiresClause() const noexcept { return _pRequiresClause; }
    void setRequiresClause(DelphiPackageRequiresClauseSyntax* requiresClause) noexcept;
    inline DelphiPackageContainsClauseSyntax* containsClause() const noexcept { return _pContainsClause; }
    void setContainsClause(DelphiPackageContainsClauseSyntax* containsClause) noexcept;

private:
    DelphiPackageHeadingSyntax* _pHeading;
    DelphiPackageRequiresClauseSyntax* _pRequiresClause;
    DelphiPackageContainsClauseSyntax* _pContainsClause;
};

} // polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPACKAGEMODULESYNTAX_H
