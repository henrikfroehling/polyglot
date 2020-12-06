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
    inline const Ptr<DelphiPackageHeadingSyntax> heading() const noexcept { return _ptrHeading; }
    inline void setHeading(Ptr<DelphiPackageHeadingSyntax> heading) noexcept { _ptrHeading = heading; }
    inline const Ptr<DelphiPackageRequiresClauseSyntax> requiresClause() const noexcept { return _ptrRequiresClause; }
    inline void setRequiresClause(Ptr<DelphiPackageRequiresClauseSyntax> requiresClause) noexcept { _ptrRequiresClause = requiresClause; }
    inline const Ptr<DelphiPackageContainsClauseSyntax>& containsClause() const noexcept { return _ptrContainsClause; }
    inline void setContainsClause(Ptr<DelphiPackageContainsClauseSyntax> containsClause) noexcept { _ptrContainsClause = containsClause; }

private:
    Ptr<DelphiPackageHeadingSyntax> _ptrHeading;
    Ptr<DelphiPackageRequiresClauseSyntax> _ptrRequiresClause;
    Ptr<DelphiPackageContainsClauseSyntax> _ptrContainsClause;
};

using DelphiPackageModuleSyntaxPtr = std::shared_ptr<DelphiPackageModuleSyntax>;

} // polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPACKAGEMODULESYNTAX_H
