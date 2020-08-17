#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPROGRAMMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPROGRAMMODULESYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiCompilationUnitSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiProgramHeadingSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUsesClauseSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiProgramModuleSyntax : public DelphiCompilationUnitSyntax
{
public:
    DelphiProgramModuleSyntax() noexcept;
    virtual ~DelphiProgramModuleSyntax() noexcept = default;
    inline bool isProgramModule() const noexcept override { return true; }
    inline const DelphiProgramHeadingSyntaxPtr& heading() const noexcept { return _ptrHeading; }
    inline void setHeading(DelphiProgramHeadingSyntaxPtr heading) noexcept { _ptrHeading = heading; }
    inline const DelphiUsesClauseSyntaxPtr& uses() const noexcept { return _ptrUses; }
    inline void setUses(DelphiUsesClauseSyntaxPtr uses) noexcept { _ptrUses = uses; }

private:
    DelphiProgramHeadingSyntaxPtr _ptrHeading;
    DelphiUsesClauseSyntaxPtr _ptrUses;
};

using DelphiProgramModuleSyntaxPtr = std::shared_ptr<DelphiProgramModuleSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPROGRAMMODULESYNTAX_H
