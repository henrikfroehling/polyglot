#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Parser.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiCompilationUnitSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiIdentifierNameSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiNameSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiPackageModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiProgramModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitFinalizationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitHeadingSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitImplementationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitInitializationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiUnitInterfaceSectionSyntax.hpp"
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
    SyntaxNodePtr parseRoot() noexcept override;
    DelphiCompilationUnitSyntaxPtr parseCompilationUnit() noexcept;
    DelphiUnitModuleSyntaxPtr parseUnitModule() noexcept;
    DelphiUnitHeadingSyntaxPtr parseUnitHeading() noexcept;
    DelphiUnitInterfaceSectionSyntaxPtr parseUnitInterfaceSection() noexcept;
    DelphiUnitImplementationSectionSyntaxPtr parseUnitImplementationSection() noexcept;
    DelphiUnitInitializationSectionSyntaxPtr parseUnitInitializationSection() noexcept;
    DelphiUnitFinalizationSectionSyntaxPtr parseUnitFinalizationSection() noexcept;
    DelphiPackageModuleSyntaxPtr parsePackageModule() noexcept;
    DelphiProgramModuleSyntaxPtr parseProgramModule() noexcept;
    DelphiNameSyntaxPtr parseQualifiedName() noexcept;

    DelphiNameSyntaxPtr parseQualifiedNameRight(DelphiNameSyntaxPtr left,
                                                SyntaxTokenPtr dotToken) noexcept;

    DelphiIdentifierNameSyntaxPtr parseIdentifierName() noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H
