#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPACKAGEMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPACKAGEMODULESYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiCompilationUnitSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiPackageContainsClauseSyntax;
class DelphiPackageHeadingSyntax;
class DelphiPackageRequiresClauseSyntax;

class POLYGLOT_API DelphiPackageModuleSyntax : public DelphiCompilationUnitSyntax
{
public:
    DelphiPackageModuleSyntax() noexcept;
    virtual ~DelphiPackageModuleSyntax() noexcept = default;
    inline bool isPackageModule() const noexcept override { return true; }
    inline DelphiPackageHeadingSyntax* heading() const noexcept { return _pHeading; }
    inline void setHeading(DelphiPackageHeadingSyntax* heading) noexcept { _pHeading = heading; }
    inline DelphiPackageRequiresClauseSyntax* requiresClause() const noexcept { return _pRequiresClause; }
    inline void setRequiresClause(DelphiPackageRequiresClauseSyntax* requiresClause) noexcept { _pRequiresClause = requiresClause; }
    inline DelphiPackageContainsClauseSyntax* containsClause() const noexcept { return _pContainsClause; }
    inline void setContainsClause(DelphiPackageContainsClauseSyntax* containsClause) noexcept { _pContainsClause = containsClause; }

private:
    DelphiPackageHeadingSyntax* _pHeading;
    DelphiPackageRequiresClauseSyntax* _pRequiresClause;
    DelphiPackageContainsClauseSyntax* _pContainsClause;
};

} // polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPACKAGEMODULESYNTAX_H
