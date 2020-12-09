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
    inline DelphiProgramHeadingSyntax* heading() const noexcept { return _ptrHeading; }
    inline void setHeading(DelphiProgramHeadingSyntax* heading) noexcept { _ptrHeading = heading; }
    inline DelphiUsesClauseSyntax* uses() const noexcept { return _ptrUses; }
    inline void setUses(DelphiUsesClauseSyntax* uses) noexcept { _ptrUses = uses; }

private:
    DelphiProgramHeadingSyntax* _ptrHeading;
    DelphiUsesClauseSyntax* _ptrUses;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPROGRAMMODULESYNTAX_H
