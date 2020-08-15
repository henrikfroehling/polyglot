#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Parser.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiCompilationUnitSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiPackageModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiProgramModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitModuleSyntax.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::CodeAnalysis
{

class SourceText;

class POLYGLOT_API DelphiParser final : public Parser
{
public:
    DelphiParser() = delete;
    explicit DelphiParser(SourceText* sourceText) noexcept;

private:
    SyntaxNodePtr parseCore() noexcept override;
    DelphiCompilationUnitSyntaxPtr parseCompilationUnit() noexcept;
    DelphiUnitModuleSyntaxPtr parseUnitModule() noexcept;
    DelphiPackageModuleSyntaxPtr parsePackageModule() noexcept;
    DelphiProgramModuleSyntaxPtr parseProgramModule() noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H
