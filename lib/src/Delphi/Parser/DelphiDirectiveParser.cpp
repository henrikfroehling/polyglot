#include "Delphi/Parser/DelphiDirectiveParser.hpp"
#include <cassert>
#include <vector>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/ISyntaxTrivia.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "Core/Syntax/Trivia/SkippedTokensTriviaSyntax.hpp"
#include "Delphi/Parser/DelphiSyntaxFacts.hpp"
#include "Delphi/Syntax/Expressions/DelphiBinaryExpressionSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiCallExpressionSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiLiteralExpressionSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiParenthesizedExpressionSyntax.hpp"
#include "Delphi/Syntax/Expressions/DelphiPrefixUnaryExpressionSyntax.hpp"
#include "Delphi/Syntax/Trivia/DelphiBadDirectiveTriviaSyntax.hpp"
#include "Delphi/Syntax/Trivia/DelphiDefineDirectiveTriviaSyntax.hpp"
#include "Delphi/Syntax/Trivia/DelphiElseDirectiveTriviaSyntax.hpp"
#include "Delphi/Syntax/Trivia/DelphiElseIfDirectiveTriviaSyntax.hpp"
#include "Delphi/Syntax/Trivia/DelphiEndIfDirectiveTriviaSyntax.hpp"
#include "Delphi/Syntax/Trivia/DelphiEndRegionDirectiveTriviaSyntax.hpp"
#include "Delphi/Syntax/Trivia/DelphiIfDefDirectiveTriviaSyntax.hpp"
#include "Delphi/Syntax/Trivia/DelphiIfDirectiveTriviaSyntax.hpp"
#include "Delphi/Syntax/Trivia/DelphiIfEndDirectiveTriviaSyntax.hpp"
#include "Delphi/Syntax/Trivia/DelphiIfNDefDirectiveTriviaSyntax.hpp"
#include "Delphi/Syntax/Trivia/DelphiMessageDirectiveTriviaSyntax.hpp"
#include "Delphi/Syntax/Trivia/DelphiRegionDirectiveTriviaSyntax.hpp"
#include "Delphi/Syntax/Trivia/DelphiSwitchDirectiveTriviaSyntax.hpp"
#include "Delphi/Syntax/Trivia/DelphiUndefDirectiveTriviaSyntax.hpp"
#include "Delphi/Syntax/DelphiIdentifierNameSyntax.hpp"

namespace polyglot::Delphi::Parser
{

using Core::Parser::DefineState;
using Core::Parser::DirectiveParser;
using Core::Parser::DirectiveStack;
using namespace Core::Syntax;
using namespace Delphi::Syntax;

DelphiDirectiveParser::DelphiDirectiveParser(SharedPtr<Core::Parser::Lexer> lexer,
                                             const DirectiveStack& context) noexcept
    : DirectiveParser{lexer, context},
      _syntaxFactory{lexer->syntaxPool()}
{}

ISyntaxTrivia* DelphiDirectiveParser::parseDirective(bool isActive,
                                                     bool endIsActive,
                                                     bool isFirstAfterTokenInFile,
                                                     bool isAfterNonWhitespaceOnLine) noexcept
{
    ISyntaxToken* pOpenBraceDollarToken = takeToken(SyntaxKind::OpenBraceDollarToken);
    assert(pOpenBraceDollarToken != nullptr);

    if (isAfterNonWhitespaceOnLine)
    {
        // TODO error handling
    }

    ISyntaxTrivia* pTrivia{nullptr};
    SyntaxKind syntaxKind = currentToken()->syntaxKind();

    switch (syntaxKind)
    {
        case SyntaxKind::IfDirectiveKeyword:
            pTrivia = parseIfDirective(pOpenBraceDollarToken, takeToken(syntaxKind), isActive);
            break;
        case SyntaxKind::IfDefDirectiveKeyword:
            pTrivia = parseIfDefDirective(pOpenBraceDollarToken, takeToken(syntaxKind), isActive);
            break;
        case SyntaxKind::IfNDefDirectiveKeyword:
            pTrivia = parseIfNDefDirective(pOpenBraceDollarToken, takeToken(syntaxKind), isActive);
            break;
        case SyntaxKind::IfEndDirectiveKeyword:
            pTrivia = parseIfEndDirective(pOpenBraceDollarToken, takeToken(syntaxKind), isActive, endIsActive);
            break;
        case SyntaxKind::ElseDirectiveKeyword:
            pTrivia = parseElseDirective(pOpenBraceDollarToken, takeToken(syntaxKind), isActive, endIsActive);
            break;
        case SyntaxKind::ElseIfDirectiveKeyword:
            pTrivia = parseElseIfDirective(pOpenBraceDollarToken, takeToken(syntaxKind), isActive, endIsActive);
            break;
        case SyntaxKind::EndIfDirectiveKeyword:
            pTrivia = parseEndIfDirective(pOpenBraceDollarToken, takeToken(syntaxKind), isActive, endIsActive);
            break;
        case SyntaxKind::DefineDirectiveKeyword:
        case SyntaxKind::UndefDirectiveKeyword:
            pTrivia = parseDefineOrUndefDirective(pOpenBraceDollarToken, takeToken(syntaxKind), isActive, endIsActive);
            break;
        case SyntaxKind::RegionDirectiveKeyword:
            pTrivia = parseRegionDirective(pOpenBraceDollarToken, takeToken(syntaxKind), isActive);
            break;
        case SyntaxKind::EndRegionDirectiveKeyword:
            pTrivia = parseEndRegionDirective(pOpenBraceDollarToken, takeToken(syntaxKind), isActive);
            break;
        case SyntaxKind::MessageDirectiveKeyword:
            pTrivia = parseMessageDirective(pOpenBraceDollarToken, takeToken(syntaxKind));
            break;
        default:
            ISyntaxToken* pIdentifier = takeToken(SyntaxKind::IdentifierToken);
            ISyntaxToken* pNextToken = peekToken(1);

            if (pNextToken->syntaxKind() == SyntaxKind::OnDirectiveKeyword || pNextToken->syntaxKind() == SyntaxKind::OffDirectiveKeyword)
                return parseSwitchDirective(pOpenBraceDollarToken, pIdentifier, takeToken());

            ISyntaxToken* pEndOfDirectiveToken = parseEndOfDirective();

            if (!isAfterNonWhitespaceOnLine)
            {
                // TODO error handling
            }

            pTrivia = DelphiBadDirectiveTriviaSyntax::create(_syntaxFactory, pOpenBraceDollarToken, pIdentifier, pEndOfDirectiveToken, isActive);
            break;
    }

    return pTrivia;
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseIfDirective(ISyntaxToken* openBraceDollarToken,
                                                               ISyntaxToken* keyword,
                                                               bool isActive) noexcept
{
    DelphiExpressionSyntax* pExpression = parseExpression();
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();
    const bool isTrue = evaluateBool(pExpression);
    const bool isBranchTaken = isActive && isTrue;
    return DelphiIfDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pExpression, pEndOfDirective, isActive, isBranchTaken, isTrue);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseIfDefDirective(ISyntaxToken* openBraceDollarToken,
                                                                  ISyntaxToken* keyword,
                                                                  bool isActive) noexcept
{
    ISyntaxToken* pIdentifier = takeToken(SyntaxKind::IdentifierToken);
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();
    const bool isBranchTaken = isActive && isDefined(pIdentifier->text());
    return DelphiIfDefDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pIdentifier, pEndOfDirective, isActive, isBranchTaken);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseIfNDefDirective(ISyntaxToken* openBraceDollarToken,
                                                                   ISyntaxToken* keyword,
                                                                   bool isActive) noexcept
{
    ISyntaxToken* pIdentifier = takeToken(SyntaxKind::IdentifierToken);
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();
    return DelphiIfNDefDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pIdentifier, pEndOfDirective, isActive);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseIfEndDirective(ISyntaxToken* openBraceDollarToken,
                                                                  ISyntaxToken* keyword,
                                                                  bool isActive,
                                                                  bool endIsActive) noexcept
{
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();
    return DelphiIfEndDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseElseDirective(ISyntaxToken* openBraceDollarToken,
                                                                 ISyntaxToken* keyword,
                                                                 bool isActive,
                                                                 bool endIsActive) noexcept
{
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();

    if (_context.hasPreviousIfOrIfNOrElseIf())
    {
        const bool isBranchTaken = endIsActive && !_context.isPreviousBranchTaken();
        return DelphiElseDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive, isBranchTaken);
    }
    else if (_context.hasUnfinishedRegion())
    {
        // TODO error handling
        return DelphiBadDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
    }
    else if (_context.hasUnfinishedIfOrIfN())
    {
        // TODO error handling
        return DelphiBadDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
    }
    else
    {
        // TODO error handling
        return DelphiBadDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
    }
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseElseIfDirective(ISyntaxToken* openBraceDollarToken,
                                                                   ISyntaxToken* keyword,
                                                                   bool isActive,
                                                                   bool endIsActive) noexcept
{
    DelphiExpressionSyntax* pExpression = parseExpression();
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();

    if (_context.hasPreviousIfOrIfNOrElseIf())
    {
        const bool isTrue = evaluateBool(pExpression);
        const bool isBranchTaken = endIsActive && isTrue && !_context.isPreviousBranchTaken();
        return DelphiElseIfDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pExpression, pEndOfDirective, isActive, isBranchTaken, isTrue);
    }
    else
    {
        // TODO error handling

        if (_context.hasUnfinishedRegion())
        {
            // TODO error handling
            return DelphiBadDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
        }
        else if (_context.hasUnfinishedIfOrIfN())
        {
            // TODO error handling
            return DelphiBadDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
        }
        else
        {
            // TODO error handling
            return DelphiBadDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
        }
    }
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseEndIfDirective(ISyntaxToken* openBraceDollarToken,
                                                                  ISyntaxToken* keyword,
                                                                  bool isActive,
                                                                  bool endIsActive) noexcept
{
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();

    if (_context.hasUnfinishedIfOrIfN())
        return DelphiEndIfDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
    else if (_context.hasUnfinishedRegion())
    {
        // TODO error handling
        return DelphiBadDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
    }
    else
    {
        // TODO error handling
        return DelphiBadDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
    }
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseDefineOrUndefDirective(ISyntaxToken* openBraceDollarToken,
                                                                          ISyntaxToken* keyword,
                                                                          bool isActive,
                                                                          bool isFollowingToken) noexcept
{
    if (isFollowingToken)
    {
        // TODO error handling
    }

    ISyntaxToken* pName = takeToken(SyntaxKind::IdentifierToken);
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();

    if (keyword->syntaxKind() == SyntaxKind::DefineDirectiveKeyword)
        return DelphiDefineDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pName, pEndOfDirective, isActive);
    else
        return DelphiUndefDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pName, pEndOfDirective, isActive);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseRegionDirective(ISyntaxToken* openBraceDollarToken,
                                                                   ISyntaxToken* keyword,
                                                                   bool isActive) noexcept
{
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();
    return DelphiRegionDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseEndRegionDirective(ISyntaxToken* openBraceDollarToken,
                                                                      ISyntaxToken* keyword,
                                                                      bool isActive) noexcept
{
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();

    if (_context.hasUnfinishedRegion())
        return DelphiEndRegionDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
    else if (_context.hasUnfinishedIfOrIfN())
    {
        // TODO error handling
        return DelphiBadDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
    }
    else
    {
        // TODO error handling
        return DelphiBadDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
    }
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseMessageDirective(ISyntaxToken* openBraceDollarToken,
                                                                    ISyntaxToken* keyword) noexcept
{
    ISyntaxToken* pMessageType{nullptr};

    if (peekToken(1)->syntaxKind() == SyntaxKind::IdentifierToken)
        pMessageType = takeToken();

    ISyntaxToken* pMessage = takeToken(SyntaxKind::SingleQuotationStringLiteralToken);
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();

    return DelphiMessageDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pMessageType, pMessage, pEndOfDirective);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseSwitchDirective(ISyntaxToken* openBraceDollarToken,
                                                                   ISyntaxToken* identifier,
                                                                   ISyntaxToken* onOffToken) noexcept
{
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();
    return DelphiSwitchDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, identifier, onOffToken, pEndOfDirective);
}

ISyntaxToken* DelphiDirectiveParser::parseEndOfDirective() noexcept
{
    std::vector<SyntaxVariant> skippedTokens{};

    if (currentToken()->syntaxKind() != SyntaxKind::EndOfDirectiveToken
        && currentToken()->syntaxKind() != SyntaxKind::EndOfFileToken)
    {
        // TODO error handling

        while (currentToken()->syntaxKind() != SyntaxKind::EndOfDirectiveToken
               && currentToken()->syntaxKind() != SyntaxKind::EndOfFileToken)
        {
            skippedTokens.push_back(SyntaxVariant::asToken(takeToken()));
        }
    }

    ISyntaxToken* pEndOfDirective{nullptr};

    if (currentToken()->syntaxKind() == SyntaxKind::EndOfDirectiveToken)
        pEndOfDirective = takeToken();
    else
        pEndOfDirective = _syntaxFactory.missingToken(SyntaxKind::EndOfDirectiveToken, L"", currentToken()->position());

    if (skippedTokens.size() > 0)
    {
        auto ptrSkippedTokensTrivia = std::make_unique<SkippedTokensTriviaSyntax>(SyntaxKind::SkippedTokensTrivia, std::move(skippedTokens));
        SkippedTokensTriviaSyntax* skippedTokensTrivia = static_cast<SkippedTokensTriviaSyntax*>(_syntaxFactory.addSyntaxTrivia(std::move(ptrSkippedTokensTrivia)));

        pEndOfDirective = _syntaxFactory.tokenWithLeadingTrivia(pEndOfDirective->syntaxKind(), pEndOfDirective->text(), pEndOfDirective->position(),
                                                                _syntaxFactory.syntaxTriviaList({skippedTokensTrivia}));
    }

    return pEndOfDirective;
}

DelphiExpressionSyntax* DelphiDirectiveParser::parseExpression() noexcept
{
    return parseLogicalOr();
}

DelphiExpressionSyntax* DelphiDirectiveParser::parseLogicalOr() noexcept
{
    DelphiExpressionSyntax* pLeftExpression = parseLogicalAnd();

    while (currentToken()->syntaxKind() == SyntaxKind::OrKeyword)
    {
        ISyntaxToken* pOperatorToken = takeToken();
        DelphiExpressionSyntax* pRightExpression = parseLogicalAnd();
        pLeftExpression = DelphiBinaryExpressionSyntax::create(_syntaxFactory, SyntaxKind::LogicalOrExpression, pLeftExpression, pOperatorToken, pRightExpression);
    }

    return pLeftExpression;
}

DelphiExpressionSyntax* DelphiDirectiveParser::parseLogicalAnd() noexcept
{
    DelphiExpressionSyntax* pLeftExpression = parseEquality();

    while (currentToken()->syntaxKind() == SyntaxKind::AndKeyword)
    {
        ISyntaxToken* pOperatorToken = takeToken();
        DelphiExpressionSyntax* pRightExpression = parseEquality();
        pLeftExpression = DelphiBinaryExpressionSyntax::create(_syntaxFactory, SyntaxKind::LogicalAndExpression, pLeftExpression, pOperatorToken, pRightExpression);
    }

    return pLeftExpression;
}

DelphiExpressionSyntax* DelphiDirectiveParser::parseEquality() noexcept
{
    DelphiExpressionSyntax* pLeftExpression = parseLogicalNot();
    SyntaxKind currentSyntaxKind = currentToken()->syntaxKind();

    while (DelphiSyntaxFacts::isComparisonSyntaxKind(currentSyntaxKind))
    {
        ISyntaxToken* pOperatorToken = takeToken();
        DelphiExpressionSyntax* pRightExpression = parseEquality();
        SyntaxKind expressionKind = DelphiSyntaxFacts::binaryExpressionKind(pOperatorToken->syntaxKind());
        pLeftExpression = DelphiBinaryExpressionSyntax::create(_syntaxFactory, expressionKind, pLeftExpression, pOperatorToken, pRightExpression);
        currentSyntaxKind = currentToken()->syntaxKind();
    }

    return pLeftExpression;
}

DelphiExpressionSyntax* DelphiDirectiveParser::parseLogicalNot() noexcept
{
    if (currentToken()->syntaxKind() == SyntaxKind::NotKeyword)
    {
        ISyntaxToken* pOperatorToken = takeToken();
        return DelphiPrefixUnaryExpressionSyntax::create(_syntaxFactory, SyntaxKind::LogicalNotExpression, pOperatorToken, parseLogicalNot());
    }

    return parsePrimary();
}

DelphiExpressionSyntax* DelphiDirectiveParser::parsePrimary() noexcept
{
    SyntaxKind syntaxKind = currentToken()->syntaxKind();

    switch (syntaxKind)
    {
        case SyntaxKind::OpenParenthesisToken:
        {
            ISyntaxToken* pOpenParenthesisToken = takeToken();
            DelphiExpressionSyntax* pExpression = parseExpression();
            ISyntaxToken* pCloseParenthesisToken = takeToken(SyntaxKind::CloseParenthesisToken);
            return DelphiParenthesizedExpressionSyntax::create(_syntaxFactory, pOpenParenthesisToken, pExpression, pCloseParenthesisToken);
        }
        case SyntaxKind::IdentifierToken:
        {
            ISyntaxToken* pIdentifier = takeToken();

            if (peekToken(1)->syntaxKind() == SyntaxKind::OpenParenthesisToken)
                return parseCallExpression(pIdentifier);

            return DelphiIdentifierNameSyntax::create(_syntaxFactory, pIdentifier);
        }
        case SyntaxKind::NumberLiteralToken:
            return DelphiLiteralExpressionSyntax::create(_syntaxFactory, SyntaxKind::NumericLiteralExpression, takeToken());
        case SyntaxKind::TrueKeyword:
        case SyntaxKind::FalseKeyword:
            return DelphiLiteralExpressionSyntax::create(_syntaxFactory, DelphiSyntaxFacts::literalExpressionKind(syntaxKind), takeToken());
        default:
            return DelphiIdentifierNameSyntax::create(_syntaxFactory, takeToken(SyntaxKind::IdentifierToken));
    }

    return nullptr;
}

DelphiExpressionSyntax* DelphiDirectiveParser::parseCallExpression(ISyntaxToken* identifier) noexcept
{
    ISyntaxToken* pOpenParenthesisToken = takeToken(SyntaxKind::OpenParenthesisToken);
    DelphiExpressionSyntax* pExpression = parseExpression();
    ISyntaxToken* pCloseParenthesisToken = takeToken(SyntaxKind::CloseParenthesisToken);
    return DelphiCallExpressionSyntax::create(_syntaxFactory, SyntaxKind::CallExpression, identifier, pOpenParenthesisToken, pExpression, pCloseParenthesisToken);
}

bool DelphiDirectiveParser::evaluateBool(DelphiExpressionSyntax* expression) const noexcept
{
    switch (expression->syntaxKind())
    {
        case SyntaxKind::CallExpression:
            return evaluateBool(static_cast<DelphiCallExpressionSyntax*>(expression)->argumentExpression());
        case SyntaxKind::LogicalNotExpression:
            return !evaluateBool(static_cast<DelphiPrefixUnaryExpressionSyntax*>(expression)->operandExpression());
        case SyntaxKind::LogicalOrExpression:
        case SyntaxKind::LogicalAndExpression:
        case SyntaxKind::EqualsExpression:
        case SyntaxKind::NotEqualsExpression:
        {
            DelphiBinaryExpressionSyntax* pBinaryExpression = static_cast<DelphiBinaryExpressionSyntax*>(expression);
            assert(pBinaryExpression != nullptr);

            switch (pBinaryExpression->syntaxKind())
            {
                case SyntaxKind::LogicalOrExpression:
                    return evaluateBool(pBinaryExpression->leftExpression()) || evaluateBool(pBinaryExpression->rightExpression());
                case SyntaxKind::LogicalAndExpression:
                    return evaluateBool(pBinaryExpression->leftExpression()) && evaluateBool(pBinaryExpression->rightExpression());
                case SyntaxKind::EqualsExpression:
                    return evaluateBool(pBinaryExpression->leftExpression()) == evaluateBool(pBinaryExpression->rightExpression());
                case SyntaxKind::NotEqualsExpression:
                    return evaluateBool(pBinaryExpression->leftExpression()) != evaluateBool(pBinaryExpression->rightExpression());
            }

            break;
        }
        case SyntaxKind::ParenthesizedExpression:
            return evaluateBool(static_cast<DelphiParenthesizedExpressionSyntax*>(expression)->expression());
        case SyntaxKind::TrueLiteralExpression:
        case SyntaxKind::FalseLiteralExpression:
            return static_cast<DelphiLiteralExpressionSyntax*>(expression)->token()->booleanValue();
        case SyntaxKind::IdentifierNameExpression:
            return isDefined(static_cast<DelphiIdentifierNameSyntax*>(expression)->identifier()->text());
    }

    return false;
}

bool DelphiDirectiveParser::isDefined(pg_string_view id) const noexcept
{
    DefineState state = _context.isDefined(id);

    switch (state)
    {
        case DefineState::Defined:
            return true;
        case DefineState::Undefined: // TODO lookup preprocessor symbols in compilation options
        case DefineState::Unspecified:
        default:
            return false;
    }
}

} // end namespace polyglot::Delphi::Parser
