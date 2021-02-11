#ifndef POLYGLOT_CODEANALYSIS_DELPHI_PARSER_DELPHIPARSER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_PARSER_DELPHIPARSER_H

#include "polyglot/Core/Types.hpp"
#include "CodeAnalysis/Core/SyntaxFactory.hpp"
#include "CodeAnalysis/Core/Parser/Parser.hpp"
#include "CodeAnalysis/Core/Text/SourceText.hpp"

namespace polyglot::CodeAnalysis
{

class DelphiCompilationUnitSyntax;
class DelphiEndOfModuleExpressionSyntax;
class DelphiPackageModuleSyntax;
class DelphiProgramModuleSyntax;
class DelphiUnitFinalizationSectionSyntax;
class DelphiUnitHeadSyntax;
class DelphiUnitImplementationSectionSyntax;
class DelphiUnitInitializationSectionSyntax;
class DelphiUnitInterfaceSectionSyntax;
class DelphiUnitModuleSyntax;
class DelphiUnitReferenceDeclarationSyntax;
class DelphiUsesClauseSyntax;
class IdentifierNameExpressionSyntax;
class LanguageSyntaxNode;
class LanguageSyntaxToken;
class NameExpressionSyntax;

class DelphiParser final : public Parser
{
public:
    DelphiParser() = delete;
    explicit DelphiParser(SharedPtr<SourceText> sourceText) noexcept;

private:
    LanguageSyntaxNode* parseRoot() noexcept override;
    DelphiCompilationUnitSyntax* parseCompilationUnit() noexcept;
    DelphiUnitModuleSyntax* parseUnitModule() noexcept;
    DelphiUnitHeadSyntax* parseUnitHead() noexcept;
    DelphiUnitInterfaceSectionSyntax* parseUnitInterfaceSection() noexcept;
    DelphiUnitImplementationSectionSyntax* parseUnitImplementationSection() noexcept;
    DelphiUnitInitializationSectionSyntax* parseUnitInitializationSection() noexcept;
    DelphiUnitFinalizationSectionSyntax* parseUnitFinalizationSection() noexcept;
    DelphiPackageModuleSyntax* parsePackageModule() noexcept;
    DelphiProgramModuleSyntax* parseProgramModule() noexcept;
    DelphiUsesClauseSyntax* parseUsesClause() noexcept;
    DelphiUnitReferenceDeclarationSyntax* parseUnitReference() noexcept;
    NameExpressionSyntax* parseQualifiedName() noexcept;

    NameExpressionSyntax* parseQualifiedNameRight(NameExpressionSyntax* left,
                                                  LanguageSyntaxToken* dotToken) noexcept;

    IdentifierNameExpressionSyntax* parseIdentifierName() noexcept;
    DelphiEndOfModuleExpressionSyntax* parseEndOfModule() noexcept;

private:
    SyntaxFactory _syntaxFactory;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_PARSER_DELPHIPARSER_H
