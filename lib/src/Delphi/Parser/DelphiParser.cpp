#include "Delphi/Parser/DelphiParser.hpp"
#include <cassert>
#include "polyglot/Core/Syntax/ISyntaxList.hpp"
#include "polyglot/Core/Syntax/ISyntaxNode.hpp"
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "Delphi/Parser/DelphiLexer.hpp"
#include "Delphi/Syntax/Expressions/DelphiAssignmentExpressionSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiBinaryExpressionSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiElementAccessExpressionSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiExtendedIdentifierNameSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiIdentifierNameSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiLiteralExpressionSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiParenthesizedExpressionSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiPointerTypeSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiPredefinedTypeSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiPrefixUnaryExpressionSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiQualifiedNameSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiRangeExpressionSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiSetConstructorSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiSetElementsConstructorSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiSetRangeConstructorSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiTypeSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiAssemblerStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiBlockStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiBreakStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiCaseStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiContinueStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiExceptionHandlerStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiExitStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiExpressionStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiForInStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiForStatementSyntax.hpp"
#include "Delphi/Syntax/Statements/DelphiForToStatementSyntax.hpp"
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
#include "Delphi/Syntax/DelphiBracketArgumentListSyntax.hpp"
#include "Delphi/Syntax/DelphiCaseElseClauseSyntax.hpp"
#include "Delphi/Syntax/DelphiCaseItemListSyntax.hpp"
#include "Delphi/Syntax/DelphiCaseItemSyntax.hpp"
#include "Delphi/Syntax/DelphiCaseLabelListSyntax.hpp"
#include "Delphi/Syntax/DelphiCaseLabelSyntax.hpp"
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
#include "Delphi/Syntax/DelphiSyntaxList.hpp"
#include "Delphi/Syntax/DelphiTryElseClauseSyntax.hpp"
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

// ----------------------------------
// Expressions
// ----------------------------------

DelphiExpressionSyntax* DelphiParser::parseExpression() noexcept
{
    const SyntaxKind currentSyntaxKind = currentToken()->syntaxKind();
    DelphiExpressionSyntax* pLeftOperandExpression{nullptr};

    if (DelphiSyntaxFacts::isInvalidSubExpression(currentSyntaxKind))
    {
        // error handling
        return nullptr;
    }

    if (DelphiSyntaxFacts::isPrefixUnaryExpression(currentSyntaxKind))
    {
        const SyntaxKind operatorKind = DelphiSyntaxFacts::prefixUnaryExpressionKind(currentSyntaxKind);
        ISyntaxToken* pOperatorToken = takeToken();
        DelphiExpressionSyntax* pOperandExpression = parseExpression();
        pLeftOperandExpression = DelphiPrefixUnaryExpressionSyntax::create(_syntaxFactory, operatorKind, pOperatorToken, pOperandExpression);
    }
    else if (currentSyntaxKind == SyntaxKind::VarKeyword)
    {
        // TODO parse variable declaration
    }
    else
    {
        pLeftOperandExpression = parseTerm();
    }

    return parseRightOperandExpression(pLeftOperandExpression);
}

DelphiExpressionSyntax* DelphiParser::parseRightOperandExpression(DelphiExpressionSyntax* leftOperandExpression) noexcept
{
    assert(leftOperandExpression != nullptr);

    while (true)
    {
        const SyntaxKind currentSyntaxKind = currentToken()->syntaxKind();
        SyntaxKind operatorKind;

        if (currentSyntaxKind == SyntaxKind::ColonEqualToken)
            operatorKind = SyntaxKind::AssignmentExpression;
        else if (currentSyntaxKind == SyntaxKind::DotDotToken)
            operatorKind = SyntaxKind::RangeExpression;
        else if (currentSyntaxKind == SyntaxKind::AsKeyword)
            operatorKind = SyntaxKind::AsExpression;
        else if (currentSyntaxKind == SyntaxKind::IsKeyword)
            operatorKind = SyntaxKind::IsExpression;
        else if (DelphiSyntaxFacts::isBinaryExpression(currentSyntaxKind))
            operatorKind = DelphiSyntaxFacts::binaryExpressionKind(currentSyntaxKind);
        else
            break;

        ISyntaxToken* pOperatorToken = takeToken();

        if (operatorKind == SyntaxKind::AssignmentExpression)
        {
            assert(pOperatorToken->syntaxKind() == SyntaxKind::ColonEqualToken);
            DelphiExpressionSyntax* pRightOperandExpression = parseExpression();
            leftOperandExpression = DelphiAssignmentExpressionSyntax::create(_syntaxFactory, leftOperandExpression,
                                                                             pOperatorToken, pRightOperandExpression);
        }
        else if (operatorKind == SyntaxKind::RangeExpression)
        {
            assert(pOperatorToken->syntaxKind() == SyntaxKind::DotDotToken);
            DelphiExpressionSyntax* pRightOperandExpression = parseExpression();
            leftOperandExpression = DelphiRangeExpressionSyntax::create(_syntaxFactory, leftOperandExpression,
                                                                        pOperatorToken, pRightOperandExpression);
        }
        else if (operatorKind == SyntaxKind::AsExpression)
        {
            assert(pOperatorToken->syntaxKind() == SyntaxKind::AsKeyword);
            DelphiTypeSyntax* pRightOperandType = parseType();
            leftOperandExpression = DelphiBinaryExpressionSyntax::create(_syntaxFactory, operatorKind, leftOperandExpression,
                                                                         pOperatorToken, pRightOperandType);
        }
        else if (operatorKind == SyntaxKind::IsExpression)
        {
            assert(pOperatorToken->syntaxKind() == SyntaxKind::IsKeyword);
            DelphiTypeSyntax* pRightOperandType = parseType();
            leftOperandExpression = DelphiBinaryExpressionSyntax::create(_syntaxFactory, operatorKind, leftOperandExpression,
                                                                         pOperatorToken, pRightOperandType);
        }
        else
        {
            assert(DelphiSyntaxFacts::isBinaryExpression(currentSyntaxKind));
            DelphiExpressionSyntax* pRightOperandExpression = parseExpression();
            leftOperandExpression = DelphiBinaryExpressionSyntax::create(_syntaxFactory, operatorKind, leftOperandExpression,
                                                                         pOperatorToken, pRightOperandExpression);
        }
    }

    return leftOperandExpression;
}

DelphiExpressionSyntax* DelphiParser::parseTerm() noexcept
{
    const SyntaxKind currentSyntaxKind = currentToken()->syntaxKind();
    DelphiExpressionSyntax* pTermExpression{nullptr};

    switch (currentSyntaxKind)
    {
        case SyntaxKind::IdentifierToken:
            pTermExpression = parseQualifiedName();
            break;
        case SyntaxKind::NilKeyword:
        case SyntaxKind::TrueKeyword:
        case SyntaxKind::FalseKeyword:
        case SyntaxKind::NumberLiteralToken:
        case SyntaxKind::IntegerNumberLiteralToken:
        case SyntaxKind::RealNumberLiteralToken:
        case SyntaxKind::ControlCharacterLiteral:
        case SyntaxKind::SingleQuotationSingleCharLiteralToken:
        case SyntaxKind::DoubleQuotationStringLiteralToken:
        case SyntaxKind::SingleQuotationStringLiteralToken:
            // TODO lookup string factors (e.g. a combination of quoted strings and control chars
            pTermExpression = parseLiteralExpression();
            break;
        case SyntaxKind::OpenParenthesisToken:
        {
            ISyntaxToken* pOpenParenthesisToken = takeToken();
            DelphiExpressionSyntax* pExpression = parseExpression();
            ISyntaxToken* pCloseParenthesisToken = takeToken(SyntaxKind::CloseParenthesisToken);
            pTermExpression = DelphiParenthesizedExpressionSyntax::create(_syntaxFactory, pOpenParenthesisToken, pExpression, pCloseParenthesisToken);
            break;
        }
        case SyntaxKind::OpenBracketToken:
            pTermExpression = parseSetConstructor();
            break;
        case SyntaxKind::AmpersandToken:
            if (DelphiSyntaxFacts::isPredefinedType(peekToken(1)->syntaxKind()))
                pTermExpression = parseExtendedIdentifierName();

            break;
        case SyntaxKind::CaretToken:
            pTermExpression = parsePointerType();
            break;
        default:
            if (DelphiSyntaxFacts::isPredefinedType(currentSyntaxKind))
                pTermExpression = parsePredefinedType();
            else
            {
                // TODO error handling
            }

            break;
    }

    assert(pTermExpression != nullptr);
    return parsePostFixExpression(pTermExpression);
}

DelphiExpressionSyntax* DelphiParser::parsePostFixExpression(DelphiExpressionSyntax* termExpression) noexcept
{
    assert(termExpression != nullptr);

    while (true)
    {
        const SyntaxKind currentSyntaxKind = currentToken()->syntaxKind();

        switch (currentSyntaxKind)
        {
            case SyntaxKind::OpenParenthesisToken:
                // TODO parse type cast or invocation expression
                break;
            case SyntaxKind::OpenBracketToken:
            {
                DelphiBracketArgumentListSyntax* pArguments = parseBracketArguments();
                return DelphiElementAccessExpressionSyntax::create(_syntaxFactory, termExpression, pArguments);
            }
            case SyntaxKind::CaretDotToken:
                // TODO parse pointer member access expression
                break;
            case SyntaxKind::DotToken:
                // TODO parse member access expression
                break;
            default:
                return termExpression;
        }
    }

    return nullptr;
}

DelphiTypeSyntax* DelphiParser::parseType() noexcept
{
    const SyntaxKind currentSyntaxKind = currentToken()->syntaxKind();

    if (DelphiSyntaxFacts::isPredefinedType(currentSyntaxKind))
    {
        ISyntaxToken* pPredefinedTypeToken = takeToken();
        return DelphiPredefinedTypeSyntax::create(_syntaxFactory, pPredefinedTypeToken);
    }

    if (currentSyntaxKind == SyntaxKind::IdentifierToken)
        return parseQualifiedName();

    // TODO error handling
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

DelphiSetConstructorSyntax* DelphiParser::parseSetConstructor() noexcept
{
    assert(currentToken()->syntaxKind() == SyntaxKind::OpenBracketToken);
    ISyntaxToken* pOpenBracketToken = takeToken(SyntaxKind::OpenBracketToken);
    DelphiExpressionSyntax* pFirstElement = parseExpression();

    if (pFirstElement->syntaxKind() == SyntaxKind::RangeExpression)
    {
        ISyntaxToken* pCloseBracketToken = takeToken(SyntaxKind::CloseBracketToken);
        return DelphiSetRangeConstructorSyntax::create(_syntaxFactory, pOpenBracketToken,
                                                       static_cast<DelphiRangeExpressionSyntax*>(pFirstElement), pCloseBracketToken);
    }
    else if (currentToken()->syntaxKind() == SyntaxKind::CommaToken)
    {
        std::vector<SyntaxVariant> elements{};
        elements.push_back(SyntaxVariant::asNode(pFirstElement));

        while (currentToken()->syntaxKind() != SyntaxKind::CloseBracketToken)
        {
            ISyntaxToken* pCommaToken = takeToken();
            elements.push_back(SyntaxVariant::asToken(pCommaToken));
            DelphiExpressionSyntax* pElement = parseExpression();
            elements.push_back(SyntaxVariant::asNode(pElement));
        }

        ISyntaxToken* pCloseBracketToken = takeToken(SyntaxKind::CloseBracketToken);
        DelphiSyntaxList* pElements = DelphiSyntaxList::create(_syntaxFactory, SyntaxKind::SetElementsList, std::move(elements));
        return DelphiSetElementsConstructorSyntax::create(_syntaxFactory, pOpenBracketToken, pElements, pCloseBracketToken);
    }

    // TODO error handling
    // , or .. expected
    return nullptr;
}

DelphiBracketArgumentListSyntax* DelphiParser::parseBracketArguments() noexcept
{
    assert(currentToken()->syntaxKind() == SyntaxKind::OpenBracketToken);
    ISyntaxToken* pOpenBracketToken = takeToken(SyntaxKind::OpenBracketToken);
    DelphiExpressionSyntax* pFirstArgument = parseExpression();
    std::vector<SyntaxVariant> arguments{};
    arguments.push_back(SyntaxVariant::asNode(pFirstArgument));

    while (currentToken()->syntaxKind() != SyntaxKind::CloseBracketToken)
    {
        ISyntaxToken* pCommaToken = takeToken();
        arguments.push_back(SyntaxVariant::asToken(pCommaToken));
        DelphiExpressionSyntax* pArgument = parseExpression();
        arguments.push_back(SyntaxVariant::asNode(pArgument));
    }

    ISyntaxToken* pCloseBracketToken = takeToken(SyntaxKind::CloseBracketToken);
    DelphiSyntaxList* pArguments = DelphiSyntaxList::create(_syntaxFactory, SyntaxKind::SetElementsList, std::move(arguments));
    return DelphiBracketArgumentListSyntax::create(_syntaxFactory, pOpenBracketToken, pArguments, pCloseBracketToken);
}

// ----------------------------------
// Statements
// ----------------------------------

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
        case SyntaxKind::AsmKeyword:
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
    ISyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return DelphiBlockStatementSyntax::create(_syntaxFactory, pBeginKeyword, pStatementList, pEndKeyword, pSemiColonToken);
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
    assert(currentToken()->syntaxKind() == SyntaxKind::CaseKeyword);
    ISyntaxToken* pCaseKeyword = takeToken(SyntaxKind::CaseKeyword);
    DelphiExpressionSyntax* pSelectorExpression = parseExpression();
    ISyntaxToken* pOfKeyword = takeToken(SyntaxKind::OfKeyword);
    DelphiCaseItemListSyntax* pCaseItems = parseCaseItems();
    DelphiCaseElseClauseSyntax* pElseClause{nullptr};

    if (currentToken()->syntaxKind() == SyntaxKind::ElseKeyword)
        pElseClause = parseCaseElseClause();

    ISyntaxToken* pEndKeyword = takeToken(SyntaxKind::EndKeyword);
    ISyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return DelphiCaseStatementSyntax::create(_syntaxFactory, pCaseKeyword, pSelectorExpression, pOfKeyword,
                                             pCaseItems, pEndKeyword, pSemiColonToken, pElseClause);
}

DelphiCaseItemListSyntax* DelphiParser::parseCaseItems() noexcept
{
    SyntaxKind syntaxKind = currentToken()->syntaxKind();

    if (syntaxKind != SyntaxKind::ElseKeyword && syntaxKind != SyntaxKind::EndKeyword)
    {
        std::vector<SyntaxVariant> caseItems{};
        DelphiCaseItemSyntax* pCaseItem = parseCaseItem();
        caseItems.push_back(SyntaxVariant::asNode(pCaseItem));
        syntaxKind = currentToken()->syntaxKind();

        while (syntaxKind != SyntaxKind::ElseKeyword && syntaxKind != SyntaxKind::EndKeyword)
        {
            pCaseItem = parseCaseItem();
            caseItems.push_back(SyntaxVariant::asNode(pCaseItem));
            syntaxKind = currentToken()->syntaxKind();
        }

        return DelphiCaseItemListSyntax::create(_syntaxFactory, std::move(caseItems));
    }

    return nullptr;
}

DelphiCaseItemSyntax* DelphiParser::parseCaseItem() noexcept
{
    DelphiCaseLabelListSyntax* pCaseLabels = parseCaseLabels();
    ISyntaxToken* pColonToken = takeToken(SyntaxKind::ColonToken);
    DelphiStatementSyntax* pStatement = parseStatement();
    return DelphiCaseItemSyntax::create(_syntaxFactory, pCaseLabels, pColonToken, pStatement);
}

DelphiCaseLabelListSyntax* DelphiParser::parseCaseLabels() noexcept
{
    if (currentToken()->syntaxKind() != SyntaxKind::ColonToken)
    {
        std::vector<SyntaxVariant> caseLabels{};
        DelphiCaseLabelSyntax* pCaseLabel = parseCaseLabel();
        caseLabels.push_back(SyntaxVariant::asNode(pCaseLabel));

        while (currentToken()->syntaxKind() != SyntaxKind::ColonToken)
        {
            ISyntaxToken* pCommaToken = takeToken(SyntaxKind::CommaToken);
            caseLabels.push_back(SyntaxVariant::asToken(pCommaToken));

            pCaseLabel = parseCaseLabel();
            caseLabels.push_back(SyntaxVariant::asNode(pCaseLabel));
        }

        return DelphiCaseLabelListSyntax::create(_syntaxFactory, std::move(caseLabels));
    }

    return nullptr;
}

DelphiCaseLabelSyntax* DelphiParser::parseCaseLabel() noexcept
{
    DelphiExpressionSyntax* pExpression = parseExpression();
    ISyntaxToken* pDotDotToken{nullptr};
    DelphiExpressionSyntax* pSecondExpression{nullptr};

    if (currentToken()->syntaxKind() == SyntaxKind::DotDotToken)
    {
        pDotDotToken = takeToken();
        pSecondExpression = parseExpression();
    }

    return DelphiCaseLabelSyntax::create(_syntaxFactory, pExpression, pDotDotToken, pSecondExpression);
}

DelphiCaseElseClauseSyntax* DelphiParser::parseCaseElseClause() noexcept
{
    assert(currentToken()->syntaxKind() == SyntaxKind::ElseKeyword);
    ISyntaxToken* pElseKeyword = takeToken(SyntaxKind::ElseKeyword);
    DelphiStatementListSyntax* pStatements = parseStatementList();
    return DelphiCaseElseClauseSyntax::create(_syntaxFactory, pElseKeyword, pStatements);
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
    assert(currentToken()->syntaxKind() == SyntaxKind::ForKeyword);
    ISyntaxToken* pForKeyword = takeToken(SyntaxKind::ForKeyword);
    DelphiExpressionSyntax* pInitialValueOrElementExpression = parseExpression();
    const SyntaxKind currentSyntaxKind = currentToken()->syntaxKind();

    assert(currentSyntaxKind == SyntaxKind::ToKeyword
           || currentSyntaxKind == SyntaxKind::DownToKeyword
           || currentSyntaxKind == SyntaxKind::InKeyword);

    ISyntaxToken* pToOrDownToOrInKeyword = takeToken(currentSyntaxKind);
    DelphiExpressionSyntax* pFinalValueOrCollectionExpression = parseExpression();
    ISyntaxToken* pDoKeyword = takeToken(SyntaxKind::DoKeyword);
    DelphiStatementSyntax* pStatement = parseStatement();

    if (pToOrDownToOrInKeyword->syntaxKind() == SyntaxKind::ToKeyword
        || pToOrDownToOrInKeyword->syntaxKind() == SyntaxKind::DownToKeyword)
    {
        return DelphiForToStatementSyntax::create(_syntaxFactory, pForKeyword, pInitialValueOrElementExpression,
                                                  pToOrDownToOrInKeyword, pFinalValueOrCollectionExpression,
                                                  pDoKeyword, pStatement);
    }

    return DelphiForInStatementSyntax::create(_syntaxFactory, pForKeyword, pInitialValueOrElementExpression,
                                              pToOrDownToOrInKeyword, pFinalValueOrCollectionExpression,
                                              pDoKeyword, pStatement);
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

        DelphiTryElseClauseSyntax* pTryElseClause{nullptr};

        if (currentToken()->syntaxKind() == SyntaxKind::ElseKeyword)
            pTryElseClause = parseTryElseClause();

        return DelphiExceptionHandlerBlockSyntax::create(_syntaxFactory, DelphiStatementListSyntax::create(_syntaxFactory, std::move(statements)), pTryElseClause);
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

DelphiTryElseClauseSyntax* DelphiParser::parseTryElseClause() noexcept
{
    assert(currentToken()->syntaxKind() == SyntaxKind::ElseKeyword);
    ISyntaxToken* pElseKeyword = takeToken(SyntaxKind::ElseKeyword);
    DelphiStatementListSyntax* pStatements = parseStatementList();
    return DelphiTryElseClauseSyntax::create(_syntaxFactory, pElseKeyword, pStatements);
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
    assert(currentToken()->syntaxKind() == SyntaxKind::AsmKeyword);
    ISyntaxToken* pAsmKeyword = takeToken(SyntaxKind::AsmKeyword);
    // TODO parse assembler instructions
    ISyntaxToken* pEndKeyword = takeToken(SyntaxKind::EndKeyword);
    ISyntaxToken* pSemiColonToken = takeToken(SyntaxKind::SemiColonToken);
    return DelphiAssemblerStatementSyntax::create(_syntaxFactory, pAsmKeyword, pEndKeyword, pSemiColonToken);
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
