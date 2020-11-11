#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPACKAGEMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPACKAGEMODULESYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiCompilationUnitSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageContainsClauseSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageHeadingSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageRequiresClauseSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiPackageModuleSyntax : public DelphiCompilationUnitSyntax
{
public:
    DelphiPackageModuleSyntax() noexcept;
    virtual ~DelphiPackageModuleSyntax() noexcept = default;
    inline bool isPackageModule() const noexcept override { return true; }
    inline const DelphiPackageHeadingSyntaxPtr& heading() const noexcept { return _ptrHeading; }
    inline void setHeading(DelphiPackageHeadingSyntaxPtr heading) noexcept { _ptrHeading = std::move(heading); }
    inline const DelphiPackageRequiresClauseSyntaxPtr& requiresClause() const noexcept { return _ptrRequiresClause; }
    inline void setRequiresClause(DelphiPackageRequiresClauseSyntaxPtr requiresClause) noexcept { _ptrRequiresClause = std::move(requiresClause); }
    inline const DelphiPackageContainsClauseSyntaxPtr& containsClause() const noexcept { return _ptrContainsClause; }
    inline void setContainsClause(DelphiPackageContainsClauseSyntaxPtr containsClause) noexcept { _ptrContainsClause = std::move(containsClause); }

private:
    DelphiPackageHeadingSyntaxPtr _ptrHeading;
    DelphiPackageRequiresClauseSyntaxPtr _ptrRequiresClause;
    DelphiPackageContainsClauseSyntaxPtr _ptrContainsClause;
};

using DelphiPackageModuleSyntaxPtr = std::shared_ptr<DelphiPackageModuleSyntax>;

} // polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPACKAGEMODULESYNTAX_H
