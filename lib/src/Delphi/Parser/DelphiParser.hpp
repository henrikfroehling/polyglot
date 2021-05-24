#ifndef POLYGLOT_DELPHI_PARSER_DELPHIPARSER_H
#define POLYGLOT_DELPHI_PARSER_DELPHIPARSER_H

#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Core/Parser/Parser.hpp"
#include "Core/Text/SourceText.hpp"

namespace polyglot::Core::Syntax
{

class IdentifierNameExpressionSyntax;
class ISyntaxNode;
class ISyntaxToken;
class NameExpressionSyntax;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiCompilationUnitSyntax;
class DelphiCompoundStatementSyntax;
class DelphiEndOfModuleSyntax;
class DelphiPackageModuleSyntax;
class DelphiProgramModuleSyntax;
class DelphiStatementListSyntax;
class DelphiStatementSyntax;
class DelphiUnitFinalizationSectionSyntax;
class DelphiUnitHeadSyntax;
class DelphiUnitImplementationSectionSyntax;
class DelphiUnitInitializationSectionSyntax;
class DelphiUnitInterfaceSectionSyntax;
class DelphiUnitModuleSyntax;
class DelphiUnitReferenceDeclarationSyntax;
class DelphiUsesClauseSyntax;

} // end namespace polyglot::Delphi::Syntax

namespace polyglot::Delphi::Parser
{

class DelphiParser final : public Core::Parser::Parser
{
public:
    DelphiParser() = delete;
    explicit DelphiParser(SharedPtr<Core::Text::SourceText> sourceText) noexcept;

private:
    Core::Syntax::ISyntaxNode* parseRoot() noexcept override;
    Syntax::DelphiCompilationUnitSyntax* parseCompilationUnit() noexcept;
    Syntax::DelphiUnitModuleSyntax* parseUnitModule() noexcept;
    Syntax::DelphiUnitHeadSyntax* parseUnitHead() noexcept;
    Syntax::DelphiUnitInterfaceSectionSyntax* parseUnitInterfaceSection() noexcept;
    Syntax::DelphiUnitImplementationSectionSyntax* parseUnitImplementationSection() noexcept;
    Syntax::DelphiUnitInitializationSectionSyntax* parseUnitInitializationSection() noexcept;
    Syntax::DelphiUnitFinalizationSectionSyntax* parseUnitFinalizationSection() noexcept;
    Syntax::DelphiPackageModuleSyntax* parsePackageModule() noexcept;
    Syntax::DelphiProgramModuleSyntax* parseProgramModule() noexcept;
    Syntax::DelphiUsesClauseSyntax* parseUsesClause() noexcept;
    Syntax::DelphiUnitReferenceDeclarationSyntax* parseUnitReference() noexcept;
    Core::Syntax::NameExpressionSyntax* parseQualifiedName() noexcept;

    Core::Syntax::NameExpressionSyntax* parseQualifiedNameRight(Core::Syntax::NameExpressionSyntax* left,
                                                                Core::Syntax::ISyntaxToken* dotToken) noexcept;

    Core::Syntax::IdentifierNameExpressionSyntax* parseIdentifierName() noexcept;
    Syntax::DelphiEndOfModuleSyntax* parseEndOfModule() noexcept;

    Syntax::DelphiCompoundStatementSyntax* parseCompoundStatement() noexcept;
    Syntax::DelphiStatementListSyntax* parseStatementList() noexcept;
    Syntax::DelphiStatementSyntax* parseStatement() noexcept;

private:
    Core::Syntax::SyntaxFactory _syntaxFactory;
};

} // end namespace polyglot::Delphi::Parser

#endif // POLYGLOT_DELPHI_PARSER_DELPHIPARSER_H
