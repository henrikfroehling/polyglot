#include "Delphi/Parser/DelphiParser.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxList.hpp"
#include "polyglot/Core/Syntax/ISyntaxNode.hpp"
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "Delphi/Parser/DelphiLexer.hpp"
#include "Delphi/Syntax/Expressions/DelphiExtendedIdentifierNameSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiIdentifierNameSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiLiteralExpressionSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiParenthesizedExpressionSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiPredefinedTypeSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiQualifiedNameSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiAssemblerStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiBreakStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiCaseStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiCompoundStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiContinueStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiExitStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiForStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiGotoStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiIfStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiRaiseStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiRepeatStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementListSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiTryStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiWhileStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiWithStatementSyntax.hpp"
#include "Delphi/Syntax/DelphiEndOfModuleDeclarationSyntax.hpp"
#include "Delphi/Syntax/DelphiPackageModuleSyntax.hpp"
#include "Delphi/Syntax/DelphiProgramModuleSyntax.hpp"
#include "Delphi/Syntax/DelphiSyntaxFacts.hpp"
#include "Delphi/Syntax/DelphiUnitFinalizationSectionSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitHeadSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitImplementationSectionSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitInitializationSectionSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitInterfaceSectionSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitModuleSyntax.hpp"
#include "Delphi/Syntax/DelphiUnitReferenceDeclarationSyntax.hpp"
#include "Delphi/Syntax/DelphiUsesClauseSyntax.hpp"

namespace polyglot::Delphi::Parser
{

using namespace Core::Syntax;
using namespace Delphi::Syntax;

DelphiParser::DelphiParser(SharedPtr<Core::Text::SourceText> sourceText) noexcept
    : Core::Parser::Parser{std::make_shared<DelphiLexer>(sourceText)},
      _syntaxFactory{_ptrLexer->syntaxPool()}
{}

ISyntaxNode* DelphiParser::parseRoot() noexcept
{
    if (DelphiSyntaxFacts::isStatementStart(currentToken()->syntaxKind()))
        return parseStatement();

    return nullptr;

//    if (DelphiSyntaxFacts::isModuleStart(currentToken()->syntaxKind()))
//        return parseCompilationUnit();
//    else
//    {
//        // TODO parse different entry points
//        return nullptr;
//    }
}

DelphiCompilationUnitSyntax* DelphiParser::parseCompilationUnit() noexcept
{
    ISyntaxToken* pCurrentToken = currentToken();
    DelphiCompilationUnitSyntax* pCompilationUnit = nullptr;

    switch (pCurrentToken->syntaxKind())
    {
        case SyntaxKind::UnitKeyword:
            pCompilationUnit = parseUnitModule();
            break;
        case SyntaxKind::PackageKeyword:
            pCompilationUnit = parsePackageModule();
            break;
        case SyntaxKind::ProgramKeyword:
            pCompilationUnit = parseProgramModule();
            break;
        default:
        {
            ISyntaxToken* pEOFToken = takeToken(SyntaxKind::EndOfFileToken);
            pCompilationUnit = DelphiCompilationUnitSyntax::create(_syntaxFactory, SyntaxKind::CompilationUnit, pEOFToken);
        }
    }

    assert(pCompilationUnit != nullptr);
    return pCompilationUnit;
}

DelphiUnitModuleSyntax* DelphiParser::parseUnitModule() noexcept
{
    DelphiUnitHeadSyntax* pHead = nullptr;
    DelphiUnitInterfaceSectionSyntax* pInterfaceSection = nullptr;
    DelphiUnitImplementationSectionSyntax* pImplementationSection = nullptr;
    DelphiUnitInitializationSectionSyntax* pInitializationSection = nullptr; // optional
    DelphiUnitFinalizationSectionSyntax* pFinalizationSection = nullptr; // optional, but requires initialization section

    pHead = parseUnitHead();
    pInterfaceSection = parseUnitInterfaceSection();
    pImplementationSection = parseUnitImplementationSection();

    if (currentToken()->syntaxKind() == SyntaxKind::InitializationKeyword)
    {
        pInitializationSection = parseUnitInitializationSection();

        if (currentToken()->syntaxKind() == SyntaxKind::FinalizationKeyword)
            pFinalizationSection = parseUnitFinalizationSection();
    }

    DelphiEndOfModuleDeclarationSyntax* endOfModule = parseEndOfModule();
    ISyntaxToken* pEOFToken = takeToken(SyntaxKind::EndOfFileToken);

    return DelphiUnitModuleSyntax::create(_syntaxFactory, pHead, pInterfaceSection, pImplementationSection,
                                          endOfModule, pEOFToken, pInitializationSection, pFinalizationSection);
}

DelphiUnitHeadSyntax* DelphiParser::parseUnitHead() noexcept
{
    ISyntaxToken* pUnitKeyword = takeToken(SyntaxKind::UnitKeyword);
    DelphiNameSyntax* pName = parseQualifiedName();
    ISyntaxToken* pInKeyword{nullptr};
    ISyntaxToken* pFilename{nullptr};

    if (currentToken()->syntaxKind() == SyntaxKind::InKeyword)
    {
        pInKeyword = takeToken();
        pFilename = takeToken(SyntaxKind::SingleQuotationStringLiteralToken);
    }

    ISyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return DelphiUnitHeadSyntax::create(_syntaxFactory, pUnitKeyword, pName, pSemiColonToken, pInKeyword, pFilename);
}

DelphiUnitInterfaceSectionSyntax* DelphiParser::parseUnitInterfaceSection() noexcept
{
    ISyntaxToken* pInterfaceKeyword = takeToken(SyntaxKind::InterfaceKeyword);
    DelphiUsesClauseSyntax* pUses{nullptr};

    if (currentToken()->syntaxKind() == SyntaxKind::UsesKeyword)
        pUses = parseUsesClause();

    return DelphiUnitInterfaceSectionSyntax::create(_syntaxFactory, pInterfaceKeyword, pUses);
}

DelphiUnitImplementationSectionSyntax* DelphiParser::parseUnitImplementationSection() noexcept
{
    ISyntaxToken* pImplementationKeyword = takeToken(SyntaxKind::ImplementationKeyword);
    DelphiUsesClauseSyntax* pUses{nullptr};

    if (currentToken()->syntaxKind() == SyntaxKind::UsesKeyword)
        pUses = parseUsesClause();

    return DelphiUnitImplementationSectionSyntax::create(_syntaxFactory, pImplementationKeyword, pUses);
}

DelphiUnitInitializationSectionSyntax* DelphiParser::parseUnitInitializationSection() noexcept
{
    return DelphiUnitInitializationSectionSyntax::create(_syntaxFactory);
}

DelphiUnitFinalizationSectionSyntax* DelphiParser::parseUnitFinalizationSection() noexcept
{
    return DelphiUnitFinalizationSectionSyntax::create(_syntaxFactory);
}

DelphiPackageModuleSyntax* DelphiParser::parsePackageModule() noexcept
{
    return DelphiPackageModuleSyntax::create(_syntaxFactory);
}

DelphiProgramModuleSyntax* DelphiParser::parseProgramModule() noexcept
{
    return DelphiProgramModuleSyntax::create(_syntaxFactory);
}

DelphiUsesClauseSyntax* DelphiParser::parseUsesClause() noexcept
{
    ISyntaxToken* pUsesKeyword = takeToken(SyntaxKind::UsesKeyword);
    std::vector<SyntaxVariant> unitReferences;

    DelphiUnitReferenceDeclarationSyntax* pUnitReference = parseUnitReference();
    unitReferences.push_back(SyntaxVariant::asNode(pUnitReference));

    while (currentToken()->syntaxKind() == SyntaxKind::CommaToken)
    {
        ISyntaxToken* pCommaToken = takeToken();
        pUnitReference = parseUnitReference();
        unitReferences.push_back(SyntaxVariant::asToken(pCommaToken));
        unitReferences.push_back(SyntaxVariant::asNode(pUnitReference));
    }

    ISyntaxList* pUnitReferences = _syntaxFactory.syntaxList(SyntaxKind::UnitReferencesList, std::move(unitReferences));
    ISyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return DelphiUsesClauseSyntax::create(_syntaxFactory, pUsesKeyword, pUnitReferences, pSemiColonToken);
}

DelphiUnitReferenceDeclarationSyntax* DelphiParser::parseUnitReference() noexcept
{
    if (currentToken()->syntaxKind() != SyntaxKind::IdentifierToken)
        return nullptr; // TODO error handling

    DelphiNameSyntax* pUnitName = parseQualifiedName();
    ISyntaxToken* pInKeyword{nullptr};
    ISyntaxToken* pSourceFile{nullptr};

    if (currentToken()->syntaxKind() == SyntaxKind::InKeyword)
    {
        pInKeyword = takeToken(SyntaxKind::InKeyword);
        pSourceFile = takeToken(SyntaxKind::SingleQuotationStringLiteralToken);
    }

    return DelphiUnitReferenceDeclarationSyntax::create(_syntaxFactory, pUnitName, pInKeyword, pSourceFile);
}

DelphiNameSyntax* DelphiParser::parseQualifiedName() noexcept
{
    DelphiNameSyntax* pName = parseIdentifierName();

    while (currentToken()->syntaxKind() == SyntaxKind::DotToken)
    {
        ISyntaxToken* pSeparator = takeToken();
        pName = parseQualifiedNameRight(pName, pSeparator);
    }

    return pName;
}

DelphiNameSyntax* DelphiParser::parseQualifiedNameRight(DelphiNameSyntax* left,
                                                        ISyntaxToken* dotToken) noexcept
{
    assert(dotToken != nullptr);
    assert(dotToken->syntaxKind() == SyntaxKind::DotToken);
    DelphiSimpleNameSyntax* pRight = parseIdentifierName();
    return DelphiQualifiedNameSyntax::create(_syntaxFactory, left, dotToken, pRight);
}

DelphiIdentifierNameSyntax* DelphiParser::parseIdentifierName() noexcept
{
    ISyntaxToken* pCurrentToken = currentToken();

    if (pCurrentToken->syntaxKind() == SyntaxKind::IdentifierToken)
    {
        ISyntaxToken* pIdentifier = takeToken();
        return DelphiIdentifierNameSyntax::create(_syntaxFactory, pIdentifier);
    }
    else
    {
        ISyntaxToken* pMissingIdentifier = _syntaxFactory.missingToken(SyntaxKind::IdentifierToken, pCurrentToken->text(), pCurrentToken->position());
        return DelphiIdentifierNameSyntax::create(_syntaxFactory, pMissingIdentifier);
    }
}

DelphiExtendedIdentifierNameSyntax* DelphiParser::parseExtendedIdentifierName() noexcept
{
    ISyntaxToken* pAmpersandToken = takeToken(SyntaxKind::AmpersandToken);
    assert(DelphiSyntaxFacts::isReservedWord(currentToken()->syntaxKind()));
    ISyntaxToken* pReservedKeyword = takeToken();
    return DelphiExtendedIdentifierNameSyntax::create(_syntaxFactory, pAmpersandToken, pReservedKeyword);
}

DelphiPredefinedTypeSyntax* DelphiParser::parsePredefinedType() noexcept
{
    assert(DelphiSyntaxFacts::isPredefinedType(currentToken()->syntaxKind()));
    ISyntaxToken* typeKeyword = takeToken();
    return DelphiPredefinedTypeSyntax::create(_syntaxFactory, typeKeyword);
}

DelphiEndOfModuleDeclarationSyntax* DelphiParser::parseEndOfModule() noexcept
{
    ISyntaxToken* pEndKeyword = takeToken(SyntaxKind::EndKeyword);
    ISyntaxToken* pDotToken = takeToken(SyntaxKind::DotToken);
    return DelphiEndOfModuleDeclarationSyntax::create(_syntaxFactory, pEndKeyword, pDotToken);
}

DelphiLiteralExpressionSyntax* DelphiParser::parseLiteralExpression() noexcept
{
    assert(DelphiSyntaxFacts::isLiteral(currentToken()->syntaxKind()));
    ISyntaxToken* pLiteralToken = takeToken();
    return DelphiLiteralExpressionSyntax::create(_syntaxFactory, DelphiSyntaxFacts::literalExpressionKind(pLiteralToken->syntaxKind()), pLiteralToken);
}

DelphiStatementSyntax* DelphiParser::parseStatement() noexcept
{
    // statement => [identifier | int num literal | hex num literal ':'],
    //              If Statement | Case Statement | Repeat Statement | While Statement | For Statement | With Statement
    //              | Try Statement | Raise Statement | Assembler Statement | Compound Statement | Simple Statement

    SyntaxKind currentSyntaxKind = currentToken()->syntaxKind();

    // Structured Statements
    switch (currentSyntaxKind)
    {
        case SyntaxKind::IfKeyword:
            return parseIfStatement();
        case SyntaxKind::CaseKeyword:
            return parseCaseStatement();
        case SyntaxKind::RepeatKeyword:
            return parseRepeatStatement();
        case SyntaxKind::WhileKeyword:
            return parseWhileStatement();
        case SyntaxKind::ForKeyword:
            return parseForStatement();
        case SyntaxKind::WithKeyword:
            return parseWithStatement();
        case SyntaxKind::TryKeyword:
            return parseTryStatement();
        case SyntaxKind::RaiseKeyword:
            return parseRaiseStatement();
        case SyntaxKind::AssemblerKeyword:
            return parseAssemblerStatement();
        case SyntaxKind::BeginKeyword:
            return parseCompoundStatement();
        case SyntaxKind::BreakKeyword:
            return parseBreakStatement();
        case SyntaxKind::ContinueKeyword:
            return parseContinueStatement();
        case SyntaxKind::ExitKeyword:
            return parseExitStatement();
        case SyntaxKind::GotoKeyword:
            return parseGotoStatement();
    }

    // Simple Statement
    return nullptr;
}

DelphiCompoundStatementSyntax* DelphiParser::parseCompoundStatement() noexcept
{
    ISyntaxToken* pBeginKeyword = takeToken(SyntaxKind::BeginKeyword);
    DelphiStatementListSyntax* pStatementList = parseStatementList();
    ISyntaxToken* pEndKeyword = takeToken(SyntaxKind::EndKeyword);
    return DelphiCompoundStatementSyntax::create(_syntaxFactory, pBeginKeyword, pStatementList, pEndKeyword);
}

DelphiStatementListSyntax* DelphiParser::parseStatementList() noexcept
{
    std::vector<SyntaxVariant> statements{};
    DelphiStatementSyntax* pStatement = parseStatement();
    statements.push_back(SyntaxVariant::asNode(pStatement));

    while (currentToken()->syntaxKind() == SyntaxKind::SemiColonToken && DelphiSyntaxFacts::isStatementStart(peekToken(1)->syntaxKind()))
    {
        ISyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
        statements.push_back(SyntaxVariant::asToken(pSemiColonToken));

        pStatement = parseStatement();
        statements.push_back(SyntaxVariant::asNode(pStatement));
    }

    return DelphiStatementListSyntax::create(_syntaxFactory, std::move(statements));
}

DelphiIfStatementSyntax* DelphiParser::parseIfStatement() noexcept
{
    ISyntaxToken* pIfKeyword = takeToken(SyntaxKind::IfKeyword);
    // parse expression
    ISyntaxToken* pThenKeyword = takeToken(SyntaxKind::ThenKeyword);

    std::vector<SyntaxVariant> statements{};
    DelphiStatementSyntax* pStatement = parseStatement();
    statements.push_back(SyntaxVariant::asNode(pStatement));

    while (currentToken()->syntaxKind() == SyntaxKind::ElseKeyword && DelphiSyntaxFacts::isStatementStart(peekToken(1)->syntaxKind()))
    {
        ISyntaxToken* pElseKeyword = takeToken(SyntaxKind::ElseKeyword);
        statements.push_back(SyntaxVariant::asToken(pElseKeyword));

        pStatement = parseStatement();
        statements.push_back(SyntaxVariant::asNode(pStatement));
    }

    DelphiStatementListSyntax* pStatements = DelphiStatementListSyntax::create(_syntaxFactory, std::move(statements));
    return DelphiIfStatementSyntax::create(_syntaxFactory, pIfKeyword, nullptr, pThenKeyword, pStatements);
}

DelphiCaseStatementSyntax* DelphiParser::parseCaseStatement() noexcept
{
    return nullptr;
}

DelphiRepeatStatementSyntax* DelphiParser::parseRepeatStatement() noexcept
{
    return nullptr;
}

DelphiWhileStatementSyntax* DelphiParser::parseWhileStatement() noexcept
{
    return nullptr;
}

DelphiForStatementSyntax* DelphiParser::parseForStatement() noexcept
{
    return nullptr;
}

DelphiWithStatementSyntax* DelphiParser::parseWithStatement() noexcept
{
    return nullptr;
}

DelphiTryStatementSyntax* DelphiParser::parseTryStatement() noexcept
{
    return nullptr;
}

DelphiRaiseStatementSyntax* DelphiParser::parseRaiseStatement() noexcept
{
    return nullptr;
}

DelphiAssemblerStatementSyntax* DelphiParser::parseAssemblerStatement() noexcept
{
    return nullptr;
}

DelphiBreakStatementSyntax* DelphiParser::parseBreakStatement() noexcept
{
    ISyntaxToken* pBreakKeyword = takeToken(SyntaxKind::BreakKeyword);
    return DelphiBreakStatementSyntax::create(_syntaxFactory, pBreakKeyword);
}

DelphiContinueStatementSyntax* DelphiParser::parseContinueStatement() noexcept
{
    ISyntaxToken* pContinueKeyword = takeToken(SyntaxKind::ContinueKeyword);
    return DelphiContinueStatementSyntax::create(_syntaxFactory, pContinueKeyword);
}

DelphiExitStatementSyntax* DelphiParser::parseExitStatement() noexcept
{
    ISyntaxToken* pExitKeyword = takeToken(SyntaxKind::ExitKeyword);
    DelphiParenthesizedExpressionSyntax* pExpression{nullptr};

    if (currentToken()->syntaxKind() == SyntaxKind::OpenParenthesisToken)
    {
        // TODO parseExpression
    }

    return DelphiExitStatementSyntax::create(_syntaxFactory, pExitKeyword, pExpression);
}

DelphiGotoStatementSyntax* DelphiParser::parseGotoStatement() noexcept
{
    ISyntaxToken* pGotoKeyword = takeToken(SyntaxKind::GotoKeyword);
    const SyntaxKind currentSyntaxKind = currentToken()->syntaxKind();
    ISyntaxToken* pLabelToken{nullptr};

    if (currentSyntaxKind == SyntaxKind::IdentifierToken || currentSyntaxKind == SyntaxKind::IntegerNumberLiteralToken)
        pLabelToken = takeToken(currentSyntaxKind);
    else
        pLabelToken = _syntaxFactory.missingToken(SyntaxKind::IdentifierToken, currentToken()->text(), currentToken()->position());

    return DelphiGotoStatementSyntax::create(_syntaxFactory, pGotoKeyword, pLabelToken);
}

} // end namespace polyglot::Delphi::Parser
