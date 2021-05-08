#ifndef POLYGLOT_DELPHI_PARSER_DELPHIPARSER_H
#define POLYGLOT_DELPHI_PARSER_DELPHIPARSER_H

#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Core/Parser/Parser.hpp"
#include "Core/Text/SourceText.hpp"

namespace polyglot::Delphi::Parser
{

class DelphiCompilationUnitSyntax;
class DelphiEndOfModuleSyntax;
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
class ISyntaxNode;
class ISyntaxToken;
class NameExpressionSyntax;

class DelphiParser final : public Parser
{
public:
    DelphiParser() = delete;
    explicit DelphiParser(SharedPtr<SourceText> sourceText) noexcept;

private:
    ISyntaxNode* parseRoot() noexcept override;
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
                                                  ISyntaxToken* dotToken) noexcept;

    IdentifierNameExpressionSyntax* parseIdentifierName() noexcept;
    DelphiEndOfModuleSyntax* parseEndOfModule() noexcept;

private:
    SyntaxFactory _syntaxFactory;
};

} // end namespace polyglot::Delphi::Parser

#endif // POLYGLOT_DELPHI_PARSER_DELPHIPARSER_H
