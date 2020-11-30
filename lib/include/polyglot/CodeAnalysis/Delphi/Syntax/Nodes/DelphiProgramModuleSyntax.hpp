#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPROGRAMMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPROGRAMMODULESYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiCompilationUnitSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiProgramHeadingSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiProgramModuleSyntax : public DelphiCompilationUnitSyntax
{
public:
    DelphiProgramModuleSyntax() noexcept;
    virtual ~DelphiProgramModuleSyntax() noexcept = default;
    inline bool isProgramModule() const noexcept override { return true; }
    inline const SharedPtr<DelphiProgramHeadingSyntax>& heading() const noexcept { return _ptrHeading; }
    inline void setHeading(SharedPtr<DelphiProgramHeadingSyntax> heading) noexcept { _ptrHeading = std::move(heading); }
    inline const SharedPtr<DelphiUsesClauseSyntax>& uses() const noexcept { return _ptrUses; }
    inline void setUses(SharedPtr<DelphiUsesClauseSyntax> uses) noexcept { _ptrUses = std::move(uses); }

private:
    SharedPtr<DelphiProgramHeadingSyntax> _ptrHeading;
    SharedPtr<DelphiUsesClauseSyntax> _ptrUses;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPROGRAMMODULESYNTAX_H
