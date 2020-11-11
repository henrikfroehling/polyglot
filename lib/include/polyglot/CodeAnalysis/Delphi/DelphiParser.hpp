#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Parser.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Nodes/SyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Tokens/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SourceText.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiIdentifierNameSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiNameSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiCompilationUnitSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiPackageModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiProgramModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitFinalizationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitHeadingSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitImplementationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInitializationSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitInterfaceSectionSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitModuleSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUnitReferenceDeclarationSyntax.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/Nodes/DelphiUsesClauseSyntax.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API DelphiParser final : public Parser
{
public:
    DelphiParser() = delete;
    explicit DelphiParser(SourceTextPtr sourceText) noexcept;

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
    DelphiUsesClauseSyntaxPtr parseUsesClause() noexcept;
    DelphiUnitReferenceDeclarationSyntaxPtr parseUnitReference() noexcept;
    DelphiNameSyntaxPtr parseQualifiedName() noexcept;

    DelphiNameSyntaxPtr parseQualifiedNameRight(DelphiNameSyntaxPtr left,
                                                SyntaxTokenPtr dotToken) noexcept;

    DelphiIdentifierNameSyntaxPtr parseIdentifierName() noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHIPARSER_H
