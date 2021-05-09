#include "DelphiDirectiveParser.hpp"
#include <cassert>
#include <vector>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/ISyntaxTrivia.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "Core/Syntax/Expressions/BinaryExpressionSyntax.hpp"
#include "Core/Syntax/Expressions/CallExpressionSyntax.hpp"
#include "Core/Syntax/Expressions/IdentifierNameExpressionSyntax.hpp"
#include "Core/Syntax/Expressions/LiteralExpressionSyntax.hpp"
#include "Core/Syntax/Expressions/ParenthesizedExpressionSyntax.hpp"
#include "Core/Syntax/Expressions/PrefixUnaryExpressionSyntax.hpp"
#include "Core/Syntax/Trivia/BadDirectiveTriviaSyntax.hpp"
#include "Core/Syntax/Trivia/DefineDirectiveTriviaSyntax.hpp"
#include "Core/Syntax/Trivia/ElseDirectiveTriviaSyntax.hpp"
#include "Core/Syntax/Trivia/ElseIfDirectiveTriviaSyntax.hpp"
#include "Core/Syntax/Trivia/EndIfDirectiveTriviaSyntax.hpp"
#include "Core/Syntax/Trivia/EndRegionDirectiveTriviaSyntax.hpp"
#include "Core/Syntax/Trivia/IfDefDirectiveTriviaSyntax.hpp"
#include "Core/Syntax/Trivia/IfDirectiveTriviaSyntax.hpp"
#include "Core/Syntax/Trivia/IfEndDirectiveTriviaSyntax.hpp"
#include "Core/Syntax/Trivia/IfNDefDirectiveTriviaSyntax.hpp"
#include "Core/Syntax/Trivia/MessageDirectiveTriviaSyntax.hpp"
#include "Core/Syntax/Trivia/RegionDirectiveTriviaSyntax.hpp"
#include "Core/Syntax/Trivia/SkippedTokensTriviaSyntax.hpp"
#include "Core/Syntax/Trivia/SwitchDirectiveTriviaSyntax.hpp"
#include "Core/Syntax/Trivia/UndefDirectiveTriviaSyntax.hpp"
#include "DelphiSyntaxFacts.hpp"

namespace polyglot::Delphi::Parser
{

using Core::Parser::DefineState;
using Core::Parser::DirectiveParser;
using Core::Parser::DirectiveStack;
using namespace Core::Syntax;

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

            pTrivia = BadDirectiveTriviaSyntax::create(_syntaxFactory, pOpenBraceDollarToken, pIdentifier, pEndOfDirectiveToken, isActive);
            break;
    }

    return pTrivia;
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseIfDirective(ISyntaxToken* openBraceDollarToken,
                                                               ISyntaxToken* keyword,
                                                               bool isActive) noexcept
{
    ExpressionSyntax* pExpression = parseExpression();
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();
    const bool isTrue = evaluateBool(pExpression);
    const bool isBranchTaken = isActive && isTrue;
    return IfDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pExpression, pEndOfDirective, isActive, isBranchTaken, isTrue);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseIfDefDirective(ISyntaxToken* openBraceDollarToken,
                                                                  ISyntaxToken* keyword,
                                                                  bool isActive) noexcept
{
    ISyntaxToken* pIdentifier = takeToken(SyntaxKind::IdentifierToken);
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();
    const bool isBranchTaken = isActive && isDefined(pIdentifier->text());
    return IfDefDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pIdentifier, pEndOfDirective, isActive, isBranchTaken);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseIfNDefDirective(ISyntaxToken* openBraceDollarToken,
                                                                   ISyntaxToken* keyword,
                                                                   bool isActive) noexcept
{
    ISyntaxToken* pIdentifier = takeToken(SyntaxKind::IdentifierToken);
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();
    return IfNDefDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pIdentifier, pEndOfDirective, isActive);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseIfEndDirective(ISyntaxToken* openBraceDollarToken,
                                                                  ISyntaxToken* keyword,
                                                                  bool isActive,
                                                                  bool endIsActive) noexcept
{
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();
    return IfEndDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseElseDirective(ISyntaxToken* openBraceDollarToken,
                                                                 ISyntaxToken* keyword,
                                                                 bool isActive,
                                                                 bool endIsActive) noexcept
{
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();

    if (_context.hasPreviousIfOrElseIf())
    {
        const bool isBranchTaken = endIsActive && !_context.isPreviousBranchTaken();
        return ElseDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive, isBranchTaken);
    }
    else if (_context.hasUnfinishedRegion())
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
    }
    else if (_context.hasUnfinishedIf())
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
    }
    else
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
    }
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseElseIfDirective(ISyntaxToken* openBraceDollarToken,
                                                                   ISyntaxToken* keyword,
                                                                   bool isActive,
                                                                   bool endIsActive) noexcept
{
    ExpressionSyntax* pExpression = parseExpression();
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();

    if (_context.hasPreviousIfOrElseIf())
    {
        const bool isTrue = evaluateBool(pExpression);
        const bool isBranchTaken = endIsActive && isTrue && !_context.isPreviousBranchTaken();
        return ElseIfDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pExpression, pEndOfDirective, isActive, isBranchTaken, isTrue);
    }
    else
    {
        // TODO error handling

        if (_context.hasUnfinishedRegion())
        {
            // TODO error handling
            return BadDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
        }
        else if (_context.hasUnfinishedIf())
        {
            // TODO error handling
            return BadDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
        }
        else
        {
            // TODO error handling
            return BadDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
        }
    }
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseEndIfDirective(ISyntaxToken* openBraceDollarToken,
                                                                  ISyntaxToken* keyword,
                                                                  bool isActive,
                                                                  bool endIsActive) noexcept
{
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();

    if (_context.hasUnfinishedIf())
        return EndIfDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
    else if (_context.hasUnfinishedRegion())
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
    }
    else
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
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
        return DefineDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pName, pEndOfDirective, isActive);
    else
        return UndefDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pName, pEndOfDirective, isActive);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseRegionDirective(ISyntaxToken* openBraceDollarToken,
                                                                   ISyntaxToken* keyword,
                                                                   bool isActive) noexcept
{
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();
    return RegionDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseEndRegionDirective(ISyntaxToken* openBraceDollarToken,
                                                                      ISyntaxToken* keyword,
                                                                      bool isActive) noexcept
{
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();

    if (_context.hasUnfinishedRegion())
        return EndRegionDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
    else if (_context.hasUnfinishedIf())
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
    }
    else
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pEndOfDirective, isActive);
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

    return MessageDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, keyword, pMessageType, pMessage, pEndOfDirective);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseSwitchDirective(ISyntaxToken* openBraceDollarToken,
                                                                   ISyntaxToken* identifier,
                                                                   ISyntaxToken* onOffToken) noexcept
{
    ISyntaxToken* pEndOfDirective = parseEndOfDirective();
    return SwitchDirectiveTriviaSyntax::create(_syntaxFactory, openBraceDollarToken, identifier, onOffToken, pEndOfDirective);
}

ISyntaxToken* DelphiDirectiveParser::parseEndOfDirective() noexcept
{
    std::vector<SyntaxNodeOrToken> skippedTokens{};

    if (currentToken()->syntaxKind() != SyntaxKind::EndOfDirectiveToken
        && currentToken()->syntaxKind() != SyntaxKind::EndOfFileToken)
    {
        // TODO error handling

        while (currentToken()->syntaxKind() != SyntaxKind::EndOfDirectiveToken
               && currentToken()->syntaxKind() != SyntaxKind::EndOfFileToken)
        {
            skippedTokens.push_back(SyntaxNodeOrToken::asToken(takeToken()));
        }
    }

    ISyntaxToken* pEndOfDirective{nullptr};

    if (currentToken()->syntaxKind() == SyntaxKind::EndOfDirectiveToken)
        pEndOfDirective = takeToken();
    else
        pEndOfDirective = _syntaxFactory.missingToken(SyntaxKind::EndOfDirectiveToken, "", currentToken()->position());

    if (skippedTokens.size() > 0)
    {
        auto ptrSkippedTokensTrivia = std::make_unique<SkippedTokensTriviaSyntax>(SyntaxKind::SkippedTokensTrivia, std::move(skippedTokens));
        SkippedTokensTriviaSyntax* skippedTokensTrivia = dynamic_cast<SkippedTokensTriviaSyntax*>(_syntaxFactory.addSyntaxTrivia(std::move(ptrSkippedTokensTrivia)));

        pEndOfDirective = _syntaxFactory.tokenWithLeadingTrivia(pEndOfDirective->syntaxKind(), pEndOfDirective->text(), pEndOfDirective->position(),
                                                                _syntaxFactory.syntaxTriviaList({skippedTokensTrivia}));
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
        ISyntaxToken* pOperatorToken = takeToken();
        ExpressionSyntax* pRightExpression = parseLogicalAnd();
        pLeftExpression = BinaryExpressionSyntax::create(_syntaxFactory, SyntaxKind::LogicalOrExpression, pLeftExpression, pOperatorToken, pRightExpression);
    }

    return pLeftExpression;
}

ExpressionSyntax* DelphiDirectiveParser::parseLogicalAnd() noexcept
{
    ExpressionSyntax* pLeftExpression = parseEquality();

    while (currentToken()->syntaxKind() == SyntaxKind::AndKeyword)
    {
        ISyntaxToken* pOperatorToken = takeToken();
        ExpressionSyntax* pRightExpression = parseEquality();
        pLeftExpression = BinaryExpressionSyntax::create(_syntaxFactory, SyntaxKind::LogicalAndExpression, pLeftExpression, pOperatorToken, pRightExpression);
    }

    return pLeftExpression;
}

ExpressionSyntax* DelphiDirectiveParser::parseEquality() noexcept
{
    ExpressionSyntax* pLeftExpression = parseLogicalNot();
    SyntaxKind currentSyntaxKind = currentToken()->syntaxKind();

    while (DelphiSyntaxFacts::isComparisonSyntaxKind(currentSyntaxKind))
    {
        ISyntaxToken* pOperatorToken = takeToken();
        ExpressionSyntax* pRightExpression = parseEquality();
        SyntaxKind expressionKind = DelphiSyntaxFacts::binaryExpressionKind(pOperatorToken->syntaxKind());
        pLeftExpression = BinaryExpressionSyntax::create(_syntaxFactory, expressionKind, pLeftExpression, pOperatorToken, pRightExpression);
        currentSyntaxKind = currentToken()->syntaxKind();
    }

    return pLeftExpression;
}

ExpressionSyntax* DelphiDirectiveParser::parseLogicalNot() noexcept
{
    if (currentToken()->syntaxKind() == SyntaxKind::NotKeyword)
    {
        ISyntaxToken* pOperatorToken = takeToken();
        return PrefixUnaryExpressionSyntax::create(_syntaxFactory, SyntaxKind::LogicalNotExpression, pOperatorToken, parseLogicalNot());
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
            ISyntaxToken* pOpenParenthesisToken = takeToken();
            ExpressionSyntax* pExpression = parseExpression();
            ISyntaxToken* pCloseParenthesisToken = takeToken(SyntaxKind::CloseParenthesisToken);
            return ParenthesizedExpressionSyntax::create(_syntaxFactory, pOpenParenthesisToken, pExpression, pCloseParenthesisToken);
        }
        case SyntaxKind::IdentifierToken:
        {
            ISyntaxToken* pIdentifier = takeToken();

            if (peekToken(1)->syntaxKind() == SyntaxKind::OpenParenthesisToken)
                return parseCallExpression(pIdentifier);

            return IdentifierNameExpressionSyntax::create(_syntaxFactory, pIdentifier);
        }
        case SyntaxKind::NumberLiteralToken:
            return LiteralExpressionSyntax::create(_syntaxFactory, SyntaxKind::NumericLiteralExpression, takeToken());
        case SyntaxKind::TrueKeyword:
        case SyntaxKind::FalseKeyword:
            return LiteralExpressionSyntax::create(_syntaxFactory, DelphiSyntaxFacts::literalExpressionKind(syntaxKind), takeToken());
        default:
            return IdentifierNameExpressionSyntax::create(_syntaxFactory, takeToken(SyntaxKind::IdentifierToken));
    }

    return nullptr;
}

ExpressionSyntax* DelphiDirectiveParser::parseCallExpression(ISyntaxToken* identifier) noexcept
{
    ISyntaxToken* pOpenParenthesisToken = takeToken(SyntaxKind::OpenParenthesisToken);
    ExpressionSyntax* pExpression = parseExpression();
    ISyntaxToken* pCloseParenthesisToken = takeToken(SyntaxKind::CloseParenthesisToken);
    return CallExpressionSyntax::create(_syntaxFactory, SyntaxKind::CallExpression, identifier, pOpenParenthesisToken, pExpression, pCloseParenthesisToken);
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
            return static_cast<LiteralExpressionSyntax*>(expression)->token()->booleanValue();
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

} // end namespace polyglot::Delphi::Parser
