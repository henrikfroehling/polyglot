#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPACKAGEMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPACKAGEMODULESYNTAX_H

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
    inline DelphiPackageHeadingSyntax* heading() const noexcept { return _ptrHeading; }
    inline void setHeading(DelphiPackageHeadingSyntax* heading) noexcept { _ptrHeading = heading; }
    inline DelphiPackageRequiresClauseSyntax* requiresClause() const noexcept { return _ptrRequiresClause; }
    inline void setRequiresClause(DelphiPackageRequiresClauseSyntax* requiresClause) noexcept { _ptrRequiresClause = requiresClause; }
    inline DelphiPackageContainsClauseSyntax* containsClause() const noexcept { return _ptrContainsClause; }
    inline void setContainsClause(DelphiPackageContainsClauseSyntax* containsClause) noexcept { _ptrContainsClause = containsClause; }

private:
    DelphiPackageHeadingSyntax* _ptrHeading;
    DelphiPackageRequiresClauseSyntax* _ptrRequiresClause;
    DelphiPackageContainsClauseSyntax* _ptrContainsClause;
};

} // polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPACKAGEMODULESYNTAX_H
