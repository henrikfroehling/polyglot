#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPACKAGEMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPACKAGEMODULESYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
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
    inline const SharedPtr<DelphiPackageHeadingSyntax>& heading() const noexcept { return _ptrHeading; }
    inline void setHeading(SharedPtr<DelphiPackageHeadingSyntax> heading) noexcept { _ptrHeading = std::move(heading); }
    inline const SharedPtr<DelphiPackageRequiresClauseSyntax>& requiresClause() const noexcept { return _ptrRequiresClause; }
    inline void setRequiresClause(SharedPtr<DelphiPackageRequiresClauseSyntax> requiresClause) noexcept { _ptrRequiresClause = std::move(requiresClause); }
    inline const SharedPtr<DelphiPackageContainsClauseSyntax>& containsClause() const noexcept { return _ptrContainsClause; }
    inline void setContainsClause(SharedPtr<DelphiPackageContainsClauseSyntax> containsClause) noexcept { _ptrContainsClause = std::move(containsClause); }

private:
    SharedPtr<DelphiPackageHeadingSyntax> _ptrHeading;
    SharedPtr<DelphiPackageRequiresClauseSyntax> _ptrRequiresClause;
    SharedPtr<DelphiPackageContainsClauseSyntax> _ptrContainsClause;
};

using DelphiPackageModuleSyntaxPtr = std::shared_ptr<DelphiPackageModuleSyntax>;

} // polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPACKAGEMODULESYNTAX_H
