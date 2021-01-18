#include "CodeAnalysis/Delphi/DelphiDirectiveParser.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/BinaryExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/CallExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/IdentifierNameExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/LiteralExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/ParenthesizedExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/PrefixUnaryExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/BadDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/DefineDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/ElseDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/ElseIfDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/EndIfDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/EndRegionDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/IfDefDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/IfDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/IfEndDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/IfNDefDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/MessageDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/RegionDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/SkippedTokensTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/SwitchDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/UndefDirectiveTriviaSyntax.hpp"
#include "CodeAnalysis/Core/SyntaxPool.hpp"
#include "CodeAnalysis/Delphi/DelphiSyntaxFacts.hpp"
#include <cassert>
#include <vector>

namespace polyglot::CodeAnalysis
{

DelphiDirectiveParser::DelphiDirectiveParser(SharedPtr<Lexer> lexer,
                                             const DirectiveStack& context) noexcept
    : DirectiveParser{lexer, context}
{}

SyntaxTrivia* DelphiDirectiveParser::parseDirective(bool isActive,
                                                    bool endIsActive,
                                                    bool isFirstAfterTokenInFile,
                                                    bool isAfterNonWhitespaceOnLine) noexcept
{
    SyntaxToken* pOpenBraceDollarToken = takeToken(SyntaxKind::OpenBraceDollarToken);
    assert(pOpenBraceDollarToken != nullptr);

    if (isAfterNonWhitespaceOnLine)
    {
        // TODO error handling
    }

    SyntaxTrivia* pTrivia{nullptr};
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
            SyntaxToken* pIdentifier = takeToken(SyntaxKind::IdentifierToken);
            SyntaxToken* pNextToken = peekToken(1);

            if (pNextToken->syntaxKind() == SyntaxKind::OnDirectiveKeyword || pNextToken->syntaxKind() == SyntaxKind::OffDirectiveKeyword)
                return parseSwitchDirective(pOpenBraceDollarToken, pIdentifier, takeToken());

            SyntaxToken* pEndOfDirectiveToken = parseEndOfDirective();

            if (!isAfterNonWhitespaceOnLine)
            {
                // TODO error handling
            }

            pTrivia = BadDirectiveTriviaSyntax::create(pOpenBraceDollarToken, pIdentifier, pEndOfDirectiveToken, isActive);
            break;
    }

    return pTrivia;
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseIfDirective(SyntaxToken* openBraceDollarToken,
                                                               SyntaxToken* keyword,
                                                               bool isActive) noexcept
{
    ExpressionSyntax* pExpression = parseExpression();
    SyntaxToken* pEndOfDirective = parseEndOfDirective();
    const bool isTrue = evaluateBool(pExpression);
    const bool isBranchTaken = isActive && isTrue;
    return IfDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pExpression, pEndOfDirective, isActive, isBranchTaken, isTrue);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseIfDefDirective(SyntaxToken* openBraceDollarToken,
                                                                  SyntaxToken* keyword,
                                                                  bool isActive) noexcept
{
    SyntaxToken* pIdentifier = takeToken(SyntaxKind::IdentifierToken);
    SyntaxToken* pEndOfDirective = parseEndOfDirective();
    const bool isBranchTaken = isActive && isDefined(pIdentifier->text());
    return IfDefDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pIdentifier, pEndOfDirective, isActive, isBranchTaken);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseIfNDefDirective(SyntaxToken* openBraceDollarToken,
                                                                   SyntaxToken* keyword,
                                                                   bool isActive) noexcept
{
    SyntaxToken* pIdentifier = takeToken(SyntaxKind::IdentifierToken);
    SyntaxToken* pEndOfDirective = parseEndOfDirective();
    return IfNDefDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pIdentifier, pEndOfDirective, isActive);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseIfEndDirective(SyntaxToken* openBraceDollarToken,
                                                                  SyntaxToken* keyword,
                                                                  bool isActive,
                                                                  bool endIsActive) noexcept
{
    SyntaxToken* pEndOfDirective = parseEndOfDirective();
    return IfEndDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pEndOfDirective, isActive);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseElseDirective(SyntaxToken* openBraceDollarToken,
                                                                 SyntaxToken* keyword,
                                                                 bool isActive,
                                                                 bool endIsActive) noexcept
{
    SyntaxToken* pEndOfDirective = parseEndOfDirective();

    if (_context.hasPreviousIfOrElseIf())
    {
        const bool isBranchTaken = endIsActive && !_context.isPreviousBranchTaken();
        return ElseDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pEndOfDirective, isActive, isBranchTaken);
    }
    else if (_context.hasUnfinishedRegion())
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pEndOfDirective, isActive);
    }
    else if (_context.hasUnfinishedIf())
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pEndOfDirective, isActive);
    }
    else
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pEndOfDirective, isActive);
    }
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseElseIfDirective(SyntaxToken* openBraceDollarToken,
                                                                   SyntaxToken* keyword,
                                                                   bool isActive,
                                                                   bool endIsActive) noexcept
{
    ExpressionSyntax* pExpression = parseExpression();
    SyntaxToken* pEndOfDirective = parseEndOfDirective();

    if (_context.hasPreviousIfOrElseIf())
    {
        const bool isTrue = evaluateBool(pExpression);
        const bool isBranchTaken = endIsActive && isTrue && !_context.isPreviousBranchTaken();
        return ElseIfDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pExpression, pEndOfDirective, isActive, isBranchTaken, isTrue);
    }
    else
    {
        // TODO error handling

        if (_context.hasUnfinishedRegion())
        {
            // TODO error handling
            return BadDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pEndOfDirective, isActive);
        }
        else if (_context.hasUnfinishedIf())
        {
            // TODO error handling
            return BadDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pEndOfDirective, isActive);
        }
        else
        {
            // TODO error handling
            return BadDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pEndOfDirective, isActive);
        }
    }
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseEndIfDirective(SyntaxToken* openBraceDollarToken,
                                                                  SyntaxToken* keyword,
                                                                  bool isActive,
                                                                  bool endIsActive) noexcept
{
    SyntaxToken* pEndOfDirective = parseEndOfDirective();

    if (_context.hasUnfinishedIf())
        return EndIfDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pEndOfDirective, isActive);
    else if (_context.hasUnfinishedRegion())
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pEndOfDirective, isActive);
    }
    else
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pEndOfDirective, isActive);
    }
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseDefineOrUndefDirective(SyntaxToken* openBraceDollarToken,
                                                                          SyntaxToken* keyword,
                                                                          bool isActive,
                                                                          bool isFollowingToken) noexcept
{
    if (isFollowingToken)
    {
        // TODO error handling
    }

    SyntaxToken* pName = takeToken(SyntaxKind::IdentifierToken);
    SyntaxToken* pEndOfDirective = parseEndOfDirective();

    if (keyword->syntaxKind() == SyntaxKind::DefineDirectiveKeyword)
        return DefineDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pName, pEndOfDirective, isActive);
    else
        return UndefDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pName, pEndOfDirective, isActive);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseRegionDirective(SyntaxToken* openBraceDollarToken,
                                                                   SyntaxToken* keyword,
                                                                   bool isActive) noexcept
{
    SyntaxToken* pEndOfDirective = parseEndOfDirective();
    return RegionDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pEndOfDirective, isActive);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseEndRegionDirective(SyntaxToken* openBraceDollarToken,
                                                                      SyntaxToken* keyword,
                                                                      bool isActive) noexcept
{
    SyntaxToken* pEndOfDirective = parseEndOfDirective();

    if (_context.hasUnfinishedRegion())
        return EndRegionDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pEndOfDirective, isActive);
    else if (_context.hasUnfinishedIf())
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pEndOfDirective, isActive);
    }
    else
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pEndOfDirective, isActive);
    }
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseMessageDirective(SyntaxToken* openBraceDollarToken,
                                                                    SyntaxToken* keyword) noexcept
{
    SyntaxToken* pMessageType{nullptr};

    if (peekToken(1)->syntaxKind() == SyntaxKind::IdentifierToken)
        pMessageType = takeToken();

    SyntaxToken* pMessage = takeToken(SyntaxKind::SingleQuotationStringLiteralToken);
    SyntaxToken* pEndOfDirective = parseEndOfDirective();

    return MessageDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, pMessageType, pMessage, pEndOfDirective);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseSwitchDirective(SyntaxToken* openBraceDollarToken,
                                                                   SyntaxToken* identifier,
                                                                   SyntaxToken* onOffToken) noexcept
{
    SyntaxToken* pEndOfDirective = parseEndOfDirective();
    return SwitchDirectiveTriviaSyntax::create(openBraceDollarToken, identifier, onOffToken, pEndOfDirective);
}

SyntaxToken* DelphiDirectiveParser::parseEndOfDirective() noexcept
{
    std::vector<SyntaxToken*> skippedTokens{};

    if (currentToken()->syntaxKind() != SyntaxKind::EndOfDirectiveToken
        && currentToken()->syntaxKind() != SyntaxKind::EndOfFileToken)
    {
        // TODO error handling

        while (currentToken()->syntaxKind() != SyntaxKind::EndOfDirectiveToken
               && currentToken()->syntaxKind() != SyntaxKind::EndOfFileToken)
        {
            skippedTokens.push_back(takeToken());
        }
    }

    SyntaxToken* pEndOfDirective{nullptr};

    if (currentToken()->syntaxKind() == SyntaxKind::EndOfDirectiveToken)
        pEndOfDirective = takeToken();
    else
    {
        auto ptrEndOfDirective = std::make_unique<SyntaxToken>(SyntaxKind::EndOfDirectiveToken);
        pEndOfDirective = SyntaxPool::addSyntaxToken(std::move(ptrEndOfDirective));
    }

    if (skippedTokens.size() > 0)
    {
        auto ptrSkippedTokensTrivia = std::make_unique<SkippedTokensTriviaSyntax>(SyntaxKind::SkippedTokensTrivia, std::move(skippedTokens));
        SkippedTokensTriviaSyntax* skippedTokensTrivia = static_cast<SkippedTokensTriviaSyntax*>(SyntaxPool::addSyntaxTrivia(std::move(ptrSkippedTokensTrivia)));
        pEndOfDirective->addLeadingTrivia(skippedTokensTrivia);
    }

    return pEndOfDirective;
}

ExpressionSyntax* DelphiDirectiveParser::parseExpression() noexcept
{
    return parseLogicalOr();
}

ExpressionSyntax* DelphiDirectiveParser::parseLogicalOr() noexcept
{
    ExpressionSyntax* pLeftExpression = parseLogicalAnd();

    while (currentToken()->syntaxKind() == SyntaxKind::OrKeyword)
    {
        SyntaxToken* pOperatorToken = takeToken();
        ExpressionSyntax* pRightExpression = parseLogicalAnd();
        pLeftExpression = BinaryExpressionSyntax::create(SyntaxKind::LogicalOrExpression, pLeftExpression, pOperatorToken, pRightExpression);
    }

    return pLeftExpression;
}

ExpressionSyntax* DelphiDirectiveParser::parseLogicalAnd() noexcept
{
    ExpressionSyntax* pLeftExpression = parseEquality();

    while (currentToken()->syntaxKind() == SyntaxKind::AndKeyword)
    {
        SyntaxToken* pOperatorToken = takeToken();
        ExpressionSyntax* pRightExpression = parseEquality();
        pLeftExpression = BinaryExpressionSyntax::create(SyntaxKind::LogicalAndExpression, pLeftExpression, pOperatorToken, pRightExpression);
    }

    return pLeftExpression;
}

ExpressionSyntax* DelphiDirectiveParser::parseEquality() noexcept
{
    ExpressionSyntax* pLeftExpression = parseLogicalNot();
    SyntaxKind currentSyntaxKind = currentToken()->syntaxKind();

    while (DelphiSyntaxFacts::isComparisonSyntaxKind(currentSyntaxKind))
    {
        SyntaxToken* pOperatorToken = takeToken();
        ExpressionSyntax* pRightExpression = parseEquality();
        SyntaxKind expressionKind = DelphiSyntaxFacts::binaryExpressionKind(pOperatorToken->syntaxKind());
        pLeftExpression = BinaryExpressionSyntax::create(expressionKind, pLeftExpression, pOperatorToken, pRightExpression);
        currentSyntaxKind = currentToken()->syntaxKind();
    }

    return pLeftExpression;
}

ExpressionSyntax* DelphiDirectiveParser::parseLogicalNot() noexcept
{
    if (currentToken()->syntaxKind() == SyntaxKind::NotKeyword)
    {
        SyntaxToken* pOperatorToken = takeToken();
        return PrefixUnaryExpressionSyntax::create(SyntaxKind::LogicalNotExpression, pOperatorToken, parseLogicalNot());
    }

    return parsePrimary();
}

ExpressionSyntax* DelphiDirectiveParser::parsePrimary() noexcept
{
    SyntaxKind syntaxKind = currentToken()->syntaxKind();

    switch (syntaxKind)
    {
        case SyntaxKind::OpenParenthesisToken:
        {
            SyntaxToken* pOpenParenthesisToken = takeToken();
            ExpressionSyntax* pExpression = parseExpression();
            SyntaxToken* pCloseParenthesisToken = takeToken(SyntaxKind::CloseParenthesisToken);
            return ParenthesizedExpressionSyntax::create(pOpenParenthesisToken, pExpression, pCloseParenthesisToken);
        }
        case SyntaxKind::IdentifierToken:
        {
            SyntaxToken* pIdentifier = takeToken();

            if (peekToken(1)->syntaxKind() == SyntaxKind::OpenParenthesisToken)
                return parseCallExpression(pIdentifier);

            return IdentifierNameExpressionSyntax::create(pIdentifier);
        }
        case SyntaxKind::NumberLiteralToken:
            return LiteralExpressionSyntax::create(SyntaxKind::NumericLiteralExpression, takeToken());
        case SyntaxKind::TrueKeyword:
        case SyntaxKind::FalseKeyword:
            return LiteralExpressionSyntax::create(DelphiSyntaxFacts::literalExpressionKind(syntaxKind), takeToken());
        default:
            return IdentifierNameExpressionSyntax::create(takeToken(SyntaxKind::IdentifierToken));
    }

    return nullptr;
}

ExpressionSyntax* DelphiDirectiveParser::parseCallExpression(SyntaxToken* identifier) noexcept
{
    SyntaxToken* pOpenParenthesisToken = takeToken(SyntaxKind::OpenParenthesisToken);
    ExpressionSyntax* pExpression = parseExpression();
    SyntaxToken* pCloseParenthesisToken = takeToken(SyntaxKind::CloseParenthesisToken);
    return CallExpressionSyntax::create(SyntaxKind::CallExpression, identifier, pOpenParenthesisToken, pExpression, pCloseParenthesisToken);
}

bool DelphiDirectiveParser::evaluateBool(ExpressionSyntax* expression) const noexcept
{
    switch (expression->syntaxKind())
    {
        case SyntaxKind::CallExpression:
            return evaluateBool(static_cast<CallExpressionSyntax*>(expression)->argumentExpression());
        case SyntaxKind::LogicalNotExpression:
            return !evaluateBool(static_cast<PrefixUnaryExpressionSyntax*>(expression)->operandExpression());
        case SyntaxKind::LogicalOrExpression:
        case SyntaxKind::LogicalAndExpression:
        case SyntaxKind::EqualsExpression:
        case SyntaxKind::NotEqualsExpression:
        {
            BinaryExpressionSyntax* pBinaryExpression = static_cast<BinaryExpressionSyntax*>(expression);
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
            return evaluateBool(static_cast<ParenthesizedExpressionSyntax*>(expression)->expression());
        case SyntaxKind::TrueLiteralExpression:
        case SyntaxKind::FalseLiteralExpression:
            return static_cast<LiteralExpressionSyntax*>(expression)->token()->value();
        case SyntaxKind::IdentifierNameExpression:
            return isDefined(static_cast<IdentifierNameExpressionSyntax*>(expression)->identifier()->text());
    }

    return false;
}

bool DelphiDirectiveParser::isDefined(std::string_view id) const noexcept
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

} // end namespace polyglot::CodeAnalysis
