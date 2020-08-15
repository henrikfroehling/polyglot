#ifndef POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPROGRAMMODULESYNTAX_H
#define POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPROGRAMMODULESYNTAX_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiCompilationUnitSyntax.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiProgramModuleSyntax : public DelphiCompilationUnitSyntax
{
public:
    explicit DelphiProgramModuleSyntax(SyntaxKind syntaxKind) noexcept;
    virtual ~DelphiProgramModuleSyntax() noexcept = default;
    inline bool isProgramModule() const noexcept override { return true; }
};

using DelphiProgramModuleSyntaxPtr = std::shared_ptr<DelphiProgramModuleSyntax>;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_SYNTAX_DELPHIPROGRAMMODULESYNTAX_H
