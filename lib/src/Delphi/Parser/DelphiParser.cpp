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
#include "Delphi/Syntax/Expressions/DelphiPointerTypeSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiPredefinedTypeSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiQualifiedNameSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiAssemblerStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiBlockStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiBreakStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiCaseStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiContinueStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiExceptionHandlerStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiExitStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiExpressionStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiForStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiGotoStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiIfStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiLabeledStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiRaiseStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiRepeatStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementListSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiTryExceptStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiTryFinallyStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiTryStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiWhileStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiWithStatementSyntax.hpp"
#include "Delphi/Syntax/DelphiElseClauseSyntax.hpp"
#include "Delphi/Syntax/DelphiEndOfModuleDeclarationSyntax.hpp"
#include "Delphi/Syntax/DelphiExceptionBlockSyntax.hpp"
#include "Delphi/Syntax/DelphiExceptionHandlerBlockSyntax.hpp"
#include "Delphi/Syntax/DelphiExceptionStatementBlockSyntax.hpp"
#include "Delphi/Syntax/DelphiExceptClauseSyntax.hpp"
#include "Delphi/Syntax/DelphiFinallyClauseSyntax.hpp"
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

DelphiEndOfModuleDeclarationSyntax* DelphiParser::parseEndOfModule() noexcept
{
    ISyntaxToken* pEndKeyword = takeToken(SyntaxKind::EndKeyword);
    ISyntaxToken* pDotToken = takeToken(SyntaxKind::DotToken);
    return DelphiEndOfModuleDeclarationSyntax::create(_syntaxFactory, pEndKeyword, pDotToken);
}

DelphiExpressionSyntax* DelphiParser::parseExpression() noexcept
{
    return nullptr;
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
    assert(currentToken()->syntaxKind() == SyntaxKind::AmpersandToken);
    ISyntaxToken* pAmpersandToken = takeToken(SyntaxKind::AmpersandToken);
    assert(DelphiSyntaxFacts::isReservedWord(currentToken()->syntaxKind()));
    ISyntaxToken* pReservedKeyword = takeToken();
    return DelphiExtendedIdentifierNameSyntax::create(_syntaxFactory, pAmpersandToken, pReservedKeyword);
}

DelphiPredefinedTypeSyntax* DelphiParser::parsePredefinedType() noexcept
{
    assert(DelphiSyntaxFacts::isPredefinedType(currentToken()->syntaxKind()));
    ISyntaxToken* pTypeKeyword = takeToken();
    return DelphiPredefinedTypeSyntax::create(_syntaxFactory, pTypeKeyword);
}

DelphiPointerTypeSyntax* DelphiParser::parsePointerType() noexcept
{
    assert(currentToken()->syntaxKind() == SyntaxKind::CaretToken);
    ISyntaxToken* pCaretToken = takeToken(SyntaxKind::CaretToken);
    DelphiTypeSyntax* pType{nullptr};

    SyntaxKind currentSyntaxKind = currentToken()->syntaxKind();

    if (currentSyntaxKind == SyntaxKind::IdentifierToken)
        pType = parseIdentifierName();
    else if (DelphiSyntaxFacts::isPredefinedType(currentSyntaxKind))
        pType = parsePredefinedType();
    else if (currentSyntaxKind == SyntaxKind::AmpersandToken && DelphiSyntaxFacts::isReservedWord(peekToken(1)->syntaxKind()))
        pType = parseExtendedIdentifierName();

    assert(pType != nullptr);
    return DelphiPointerTypeSyntax::create(_syntaxFactory, pCaretToken, pType);
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
    //              | Try Statement | Raise Statement | Assembler Statement | Compound Statement | Expression Statement

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
            return parseBlockStatement();
        case SyntaxKind::BreakKeyword:
            return parseBreakStatement();
        case SyntaxKind::ContinueKeyword:
            return parseContinueStatement();
        case SyntaxKind::ExitKeyword:
            return parseExitStatement();
        case SyntaxKind::GotoKeyword:
            return parseGotoStatement();
    }

    return parseExpressionStatement();
}

DelphiExpressionStatementSyntax* DelphiParser::parseExpressionStatement() noexcept
{
    DelphiExpressionSyntax* pExpression = parseExpression();
    ISyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return DelphiExpressionStatementSyntax::create(_syntaxFactory, pExpression, pSemiColonToken);
}

DelphiBlockStatementSyntax* DelphiParser::parseBlockStatement() noexcept
{
    assert(currentToken()->syntaxKind() == SyntaxKind::BeginKeyword);
    ISyntaxToken* pBeginKeyword = takeToken(SyntaxKind::BeginKeyword);
    DelphiStatementListSyntax* pStatementList = parseStatementList();
    ISyntaxToken* pEndKeyword = takeToken(SyntaxKind::EndKeyword);
    return DelphiBlockStatementSyntax::create(_syntaxFactory, pBeginKeyword, pStatementList, pEndKeyword);
}

DelphiStatementListSyntax* DelphiParser::parseStatementList() noexcept
{
    std::vector<SyntaxVariant> statements{};
    DelphiStatementSyntax* pStatement = parseStatement();
    statements.push_back(SyntaxVariant::asNode(pStatement));

    while (DelphiSyntaxFacts::isStatementStart(currentToken()->syntaxKind()))
    {
        pStatement = parseStatement();
        statements.push_back(SyntaxVariant::asNode(pStatement));
    }

    return DelphiStatementListSyntax::create(_syntaxFactory, std::move(statements));
}

DelphiIfStatementSyntax* DelphiParser::parseIfStatement() noexcept
{
    assert(currentToken()->syntaxKind() == SyntaxKind::IfKeyword);
    ISyntaxToken* pIfKeyword = takeToken(SyntaxKind::IfKeyword);
    DelphiExpressionSyntax* pConditionExpression = parseExpression();
    ISyntaxToken* pThenKeyword = takeToken(SyntaxKind::ThenKeyword);
    assert(DelphiSyntaxFacts::isStatementStart(currentToken()->syntaxKind()));
    DelphiStatementSyntax* pStatement = parseStatement();
    DelphiElseClauseSyntax* pElseClause = parseElseClause();
    return DelphiIfStatementSyntax::create(_syntaxFactory, pIfKeyword, pConditionExpression, pThenKeyword, pStatement, pElseClause);
}

DelphiElseClauseSyntax* DelphiParser::parseElseClause() noexcept
{
    if (currentToken()->syntaxKind() != SyntaxKind::ElseKeyword)
        return nullptr;

    ISyntaxToken* pElseKeyword = takeToken(SyntaxKind::ElseKeyword);
    DelphiStatementSyntax* pStatement = parseStatement();
    return DelphiElseClauseSyntax::create(_syntaxFactory, pElseKeyword, pStatement);
}

DelphiCaseStatementSyntax* DelphiParser::parseCaseStatement() noexcept
{
    return nullptr;
}

DelphiRepeatStatementSyntax* DelphiParser::parseRepeatStatement() noexcept
{
    assert(currentToken()->syntaxKind() == SyntaxKind::RepeatKeyword);
    ISyntaxToken* pRepeatKeyword = takeToken(SyntaxKind::RepeatKeyword);
    DelphiStatementSyntax* pStatement = parseStatement();
    ISyntaxToken* pUntilKeyword = takeToken(SyntaxKind::UntilKeyword);
    DelphiExpressionSyntax* pExpression = parseExpression();
    ISyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return DelphiRepeatStatementSyntax::create(_syntaxFactory, pRepeatKeyword, pStatement, pUntilKeyword, pExpression, pSemiColonToken);
}

DelphiWhileStatementSyntax* DelphiParser::parseWhileStatement() noexcept
{
    assert(currentToken()->syntaxKind() == SyntaxKind::WhileKeyword);
    ISyntaxToken* pWhileKeyword = takeToken(SyntaxKind::WhileKeyword);
    DelphiExpressionSyntax* pExpression = parseExpression();
    ISyntaxToken* pDoKeyword = takeToken(SyntaxKind::DoKeyword);
    DelphiStatementSyntax* pStatement = parseStatement();
    return DelphiWhileStatementSyntax::create(_syntaxFactory, pWhileKeyword, pExpression, pDoKeyword, pStatement);
}

DelphiForStatementSyntax* DelphiParser::parseForStatement() noexcept
{
    return nullptr;
}

DelphiWithStatementSyntax* DelphiParser::parseWithStatement() noexcept
{
    assert(currentToken()->syntaxKind() == SyntaxKind::WithKeyword);
    ISyntaxToken* pWithKeyword = takeToken(SyntaxKind::WithKeyword);
    DelphiExpressionSyntax* pExpression = parseExpression();
    ISyntaxToken* pDoKeyword = takeToken(SyntaxKind::DoKeyword);
    DelphiStatementSyntax* pStatement = parseStatement();
    return DelphiWithStatementSyntax::create(_syntaxFactory, pWithKeyword, pExpression, pDoKeyword, pStatement);
}

DelphiTryStatementSyntax* DelphiParser::parseTryStatement() noexcept
{
    assert(currentToken()->syntaxKind() == SyntaxKind::TryKeyword);
    ISyntaxToken* pTryKeyword = takeToken(SyntaxKind::TryKeyword);
    DelphiStatementListSyntax* pStatements = parseStatementList();
    DelphiExceptClauseSyntax* pExceptClause{nullptr};
    DelphiFinallyClauseSyntax* pFinallyClause{nullptr};

    if (currentToken()->syntaxKind() == SyntaxKind::ExceptKeyword)
        pExceptClause = parseExceptClause();
    else if (currentToken()->syntaxKind() == SyntaxKind::FinallyKeyword)
        pFinallyClause = parseFinallyClause();

    assert(pExceptClause != nullptr || pFinallyClause != nullptr);
    ISyntaxToken* pEndKeyword = takeToken(SyntaxKind::EndKeyword);
    ISyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);

    if (pExceptClause != nullptr)
        return DelphiTryExceptStatementSyntax::create(_syntaxFactory, pTryKeyword, pStatements, pExceptClause, pEndKeyword, pSemiColonToken);
    else if (pFinallyClause != nullptr)
        return DelphiTryFinallyStatementSyntax::create(_syntaxFactory, pTryKeyword, pStatements, pFinallyClause, pEndKeyword, pSemiColonToken);

    return nullptr;
}

DelphiExceptClauseSyntax* DelphiParser::parseExceptClause() noexcept
{
    assert(currentToken()->syntaxKind() == SyntaxKind::ExceptKeyword);
    ISyntaxToken* pExceptKeyword = takeToken(SyntaxKind::ExceptKeyword);
    DelphiExceptionBlockSyntax* pExceptionBlock = parseExceptionBlock();
    return DelphiExceptClauseSyntax::create(_syntaxFactory, pExceptKeyword, pExceptionBlock);
}

DelphiExceptionBlockSyntax* DelphiParser::parseExceptionBlock() noexcept
{
    if (currentToken()->syntaxKind() == SyntaxKind::OnKeyword)
    {
        std::vector<SyntaxVariant> statements{};
        DelphiExceptionHandlerStatementSyntax* pExceptionHandlerStatement = parseExceptionHandlerStatement();
        statements.push_back(SyntaxVariant::asNode(pExceptionHandlerStatement));

        while (currentToken()->syntaxKind() == SyntaxKind::OnKeyword)
        {
            pExceptionHandlerStatement = parseExceptionHandlerStatement();
            statements.push_back(SyntaxVariant::asNode(pExceptionHandlerStatement));
        }

        DelphiElseClauseSyntax* pElseClause{nullptr};

        if (currentToken()->syntaxKind() == SyntaxKind::ElseKeyword)
            pElseClause = parseElseClause();

        return DelphiExceptionHandlerBlockSyntax::create(_syntaxFactory, DelphiStatementListSyntax::create(_syntaxFactory, std::move(statements)), pElseClause);
    }

    DelphiStatementListSyntax* pStatements = parseStatementList();
    return DelphiExceptionStatementBlockSyntax::create(_syntaxFactory, pStatements);
}

DelphiExceptionHandlerStatementSyntax* DelphiParser::parseExceptionHandlerStatement() noexcept
{
    assert(currentToken()->syntaxKind() == SyntaxKind::OnKeyword);
    ISyntaxToken* pOnKeyword = takeToken(SyntaxKind::OnKeyword);
    DelphiExpressionSyntax* pExpression = parseExpression();
    ISyntaxToken* pDoKeyword = takeToken(SyntaxKind::DoKeyword);
    DelphiStatementSyntax* pStatement = parseStatement();
    ISyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return DelphiExceptionHandlerStatementSyntax::create(_syntaxFactory, pOnKeyword, pExpression, pDoKeyword, pStatement, pSemiColonToken);
}

DelphiFinallyClauseSyntax* DelphiParser::parseFinallyClause() noexcept
{
    assert(currentToken()->syntaxKind() == SyntaxKind::FinallyKeyword);
    ISyntaxToken* pFinallyKeyword = takeToken(SyntaxKind::FinallyKeyword);
    DelphiStatementListSyntax* pStatements = parseStatementList();
    return DelphiFinallyClauseSyntax::create(_syntaxFactory, pFinallyKeyword, pStatements);
}

DelphiRaiseStatementSyntax* DelphiParser::parseRaiseStatement() noexcept
{
    assert(currentToken()->syntaxKind() == SyntaxKind::RaiseKeyword);
    ISyntaxToken* pRaiseKeyword = takeToken(SyntaxKind::RaiseKeyword);
    DelphiExpressionSyntax* pExpression{nullptr};
    ISyntaxToken* pSemiColonToken{nullptr};

    if (currentToken()->syntaxKind() == SyntaxKind::SemiColonToken)
        pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    else
    {
        pExpression = parseExpression();
        pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    }

    assert(pSemiColonToken != nullptr);
    return DelphiRaiseStatementSyntax::create(_syntaxFactory, pRaiseKeyword, pSemiColonToken, pExpression);
}

DelphiAssemblerStatementSyntax* DelphiParser::parseAssemblerStatement() noexcept
{
    return nullptr;
}

DelphiBreakStatementSyntax* DelphiParser::parseBreakStatement() noexcept
{
    assert(currentToken()->syntaxKind() == SyntaxKind::BreakKeyword);
    ISyntaxToken* pBreakKeyword = takeToken(SyntaxKind::BreakKeyword);
    ISyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return DelphiBreakStatementSyntax::create(_syntaxFactory, pBreakKeyword, pSemiColonToken);
}

DelphiContinueStatementSyntax* DelphiParser::parseContinueStatement() noexcept
{
    assert(currentToken()->syntaxKind() == SyntaxKind::ContinueKeyword);
    ISyntaxToken* pContinueKeyword = takeToken(SyntaxKind::ContinueKeyword);
    ISyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return DelphiContinueStatementSyntax::create(_syntaxFactory, pContinueKeyword, pSemiColonToken);
}

DelphiExitStatementSyntax* DelphiParser::parseExitStatement() noexcept
{
    assert(currentToken()->syntaxKind() == SyntaxKind::ExitKeyword);
    ISyntaxToken* pExitKeyword = takeToken(SyntaxKind::ExitKeyword);
    DelphiParenthesizedExpressionSyntax* pExpression{nullptr};

    if (currentToken()->syntaxKind() == SyntaxKind::OpenParenthesisToken)
    {
        // TODO parseExpression
    }

    ISyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return DelphiExitStatementSyntax::create(_syntaxFactory, pExitKeyword, pSemiColonToken, pExpression);
}

DelphiGotoStatementSyntax* DelphiParser::parseGotoStatement() noexcept
{
    assert(currentToken()->syntaxKind() == SyntaxKind::GotoKeyword);
    ISyntaxToken* pGotoKeyword = takeToken(SyntaxKind::GotoKeyword);
    const SyntaxKind currentSyntaxKind = currentToken()->syntaxKind();
    ISyntaxToken* pLabelToken{nullptr};

    if (currentSyntaxKind == SyntaxKind::IdentifierToken || currentSyntaxKind == SyntaxKind::IntegerNumberLiteralToken)
        pLabelToken = takeToken(currentSyntaxKind);
    else
        pLabelToken = _syntaxFactory.missingToken(SyntaxKind::IdentifierToken, currentToken()->text(), currentToken()->position());

    ISyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return DelphiGotoStatementSyntax::create(_syntaxFactory, pGotoKeyword, pLabelToken, pSemiColonToken);
}

DelphiLabeledStatementSyntax* DelphiParser::parseLabeledStatement() noexcept
{
    SyntaxKind currentSyntaxKind = currentToken()->syntaxKind();
    assert(currentSyntaxKind == SyntaxKind::IdentifierToken || currentSyntaxKind == SyntaxKind::IntegerNumberLiteralToken);
    ISyntaxToken* pLabelIdentifier = takeToken(currentSyntaxKind);
    ISyntaxToken* pColonToken = takeToken(SyntaxKind::ColonToken);
    DelphiStatementSyntax* pStatement = parseStatement();
    return DelphiLabeledStatementSyntax::create(_syntaxFactory, pLabelIdentifier, pColonToken, pStatement);
}

} // end namespace polyglot::Delphi::Parser
