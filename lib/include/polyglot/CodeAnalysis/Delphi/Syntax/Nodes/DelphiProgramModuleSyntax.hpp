#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPROGRAMMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPROGRAMMODULESYNTAX_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiCompilationUnitSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiProgramHeadingSyntax;
class DelphiUsesClauseSyntax;

class POLYGLOT_API DelphiProgramModuleSyntax : public DelphiCompilationUnitSyntax
{
public:
    DelphiProgramModuleSyntax() noexcept;
    virtual ~DelphiProgramModuleSyntax() noexcept = default;
    inline bool isProgramModule() const noexcept override { return true; }
    inline DelphiProgramHeadingSyntax* heading() const noexcept { return _pHeading; }
    inline void setHeading(DelphiProgramHeadingSyntax* heading) noexcept { _pHeading = heading; }
    inline DelphiUsesClauseSyntax* uses() const noexcept { return _pUses; }
    inline void setUses(DelphiUsesClauseSyntax* uses) noexcept { _pUses = uses; }

private:
    DelphiProgramHeadingSyntax* _pHeading;
    DelphiUsesClauseSyntax* _pUses;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_NODES_DELPHIPROGRAMMODULESYNTAX_H
