#ifndef POLYGLOT_DELPHI_PARSER_DELPHIPARSER_H
#define POLYGLOT_DELPHI_PARSER_DELPHIPARSER_H

#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Core/Parser/Parser.hpp"
#include "Core/Text/SourceText.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class ISyntaxToken;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Delphi::Syntax
{

class DelphiAssemblerStatementSyntax;;
class DelphiBlockStatementSyntax;
class DelphiBreakStatementSyntax;
class DelphiCaseStatementSyntax;
class DelphiCompilationUnitSyntax;
class DelphiContinueStatementSyntax;
class DelphiEndOfModuleDeclarationSyntax;
class DelphiExitStatementSyntax;
class DelphiExpressionSyntax;
class DelphiExpressionStatementSyntax;
class DelphiExtendedIdentifierNameSyntax;
class DelphiForStatementSyntax;
class DelphiGotoStatementSyntax;
class DelphiIdentifierNameSyntax;
class DelphiIfStatementSyntax;
class DelphiLabeledStatementSyntax;
class DelphiLiteralExpressionSyntax;
class DelphiNameSyntax;
class DelphiPackageModuleSyntax;
class DelphiPointerTypeSyntax;
class DelphiPredefinedTypeSyntax;
class DelphiProgramModuleSyntax;
class DelphiRaiseStatementSyntax;
class DelphiRepeatStatementSyntax;
class DelphiStatementListSyntax;
class DelphiStatementSyntax;
class DelphiTryStatementSyntax;
class DelphiUnitFinalizationSectionSyntax;
class DelphiUnitHeadSyntax;
class DelphiUnitImplementationSectionSyntax;
class DelphiUnitInitializationSectionSyntax;
class DelphiUnitInterfaceSectionSyntax;
class DelphiUnitModuleSyntax;
class DelphiUnitReferenceDeclarationSyntax;
class DelphiUsesClauseSyntax;
class DelphiWhileStatementSyntax;
class DelphiWithStatementSyntax;

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
    Syntax::DelphiEndOfModuleDeclarationSyntax* parseEndOfModule() noexcept;

    // expressions
    Syntax::DelphiExpressionSyntax* parseExpression() noexcept;
    Syntax::DelphiNameSyntax* parseQualifiedName() noexcept;

    Syntax::DelphiNameSyntax* parseQualifiedNameRight(Syntax::DelphiNameSyntax* left,
                                                      Core::Syntax::ISyntaxToken* dotToken) noexcept;

    Syntax::DelphiIdentifierNameSyntax* parseIdentifierName() noexcept;
    Syntax::DelphiExtendedIdentifierNameSyntax* parseExtendedIdentifierName() noexcept;
    Syntax::DelphiPredefinedTypeSyntax* parsePredefinedType() noexcept;
    Syntax::DelphiPointerTypeSyntax* parsePointerType() noexcept;
    Syntax::DelphiLiteralExpressionSyntax* parseLiteralExpression() noexcept;

    // statements
    Syntax::DelphiStatementSyntax* parseStatement() noexcept;
    Syntax::DelphiExpressionStatementSyntax* parseExpressionStatement() noexcept;
    Syntax::DelphiBlockStatementSyntax* parseBlockStatement() noexcept;
    Syntax::DelphiStatementListSyntax* parseStatementList() noexcept;
    Syntax::DelphiIfStatementSyntax* parseIfStatement() noexcept;
    Syntax::DelphiCaseStatementSyntax* parseCaseStatement() noexcept;
    Syntax::DelphiRepeatStatementSyntax* parseRepeatStatement() noexcept;
    Syntax::DelphiWhileStatementSyntax* parseWhileStatement() noexcept;
    Syntax::DelphiForStatementSyntax* parseForStatement() noexcept;
    Syntax::DelphiWithStatementSyntax* parseWithStatement() noexcept;
    Syntax::DelphiTryStatementSyntax* parseTryStatement() noexcept;
    Syntax::DelphiRaiseStatementSyntax* parseRaiseStatement() noexcept;
    Syntax::DelphiAssemblerStatementSyntax* parseAssemblerStatement() noexcept;
    Syntax::DelphiBreakStatementSyntax* parseBreakStatement() noexcept;
    Syntax::DelphiContinueStatementSyntax* parseContinueStatement() noexcept;
    Syntax::DelphiExitStatementSyntax* parseExitStatement() noexcept;
    Syntax::DelphiGotoStatementSyntax* parseGotoStatement() noexcept;
    Syntax::DelphiLabeledStatementSyntax* parseLabeledStatement() noexcept;

private:
    Core::Syntax::SyntaxFactory _syntaxFactory;
};

} // end namespace polyglot::Delphi::Parser

#endif // POLYGLOT_DELPHI_PARSER_DELPHIPARSER_H
