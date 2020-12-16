#include "polyglot/CodeAnalysis/Delphi/DelphiDirectiveParser.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
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
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxFacts.hpp"
#include <cassert>
#include <vector>

namespace polyglot::CodeAnalysis
{

DelphiDirectiveParser::DelphiDirectiveParser(SharedPtr<Lexer> lexer,
                                             const DirectiveStack& context) noexcept
    : DirectiveParser{lexer, context}
{}

SyntaxNode* DelphiDirectiveParser::parseDirective(bool isActive,
                                                  bool endIsActive,
                                                  bool isFirstAfterTokenInFile,
                                                  bool isAfterNonWhitespaceOnLine) noexcept
{
    SyntaxToken* openBraceDollarToken = takeToken(SyntaxKind::OpenBraceDollarToken);
    assert(openBraceDollarToken != nullptr);

    if (isAfterNonWhitespaceOnLine)
    {
        // TODO error handling
    }

    SyntaxNode* result{nullptr};
    SyntaxKind syntaxKind = currentToken()->syntaxKind();

    switch (syntaxKind)
    {
        case SyntaxKind::IfDirectiveKeyword:
            result = parseIfDirective(openBraceDollarToken, takeToken(syntaxKind), isActive);
            break;
        case SyntaxKind::IfDefDirectiveKeyword:
            result = parseIfDefDirective(openBraceDollarToken, takeToken(syntaxKind), isActive);
            break;
        case SyntaxKind::IfNDefDirectiveKeyword:
            result = parseIfNDefDirective(openBraceDollarToken, takeToken(syntaxKind), isActive);
            break;
        case SyntaxKind::IfEndDirectiveKeyword:
            result = parseIfEndDirective(openBraceDollarToken, takeToken(syntaxKind), isActive, endIsActive);
            break;
        case SyntaxKind::ElseDirectiveKeyword:
            result = parseElseDirective(openBraceDollarToken, takeToken(syntaxKind), isActive, endIsActive);
            break;
        case SyntaxKind::ElseIfDirectiveKeyword:
            result = parseElseIfDirective(openBraceDollarToken, takeToken(syntaxKind), isActive, endIsActive);
            break;
        case SyntaxKind::EndIfDirectiveKeyword:
            result = parseEndIfDirective(openBraceDollarToken, takeToken(syntaxKind), isActive, endIsActive);
            break;
        case SyntaxKind::DefineDirectiveKeyword:
        case SyntaxKind::UndefDirectiveKeyword:
            result = parseDefineOrUndefDirective(openBraceDollarToken, takeToken(syntaxKind), isActive, endIsActive);
            break;
        case SyntaxKind::RegionDirectiveKeyword:
            result = parseRegionDirective(openBraceDollarToken, takeToken(syntaxKind), isActive);
            break;
        case SyntaxKind::EndRegionDirectiveKeyword:
            result = parseEndRegionDirective(openBraceDollarToken, takeToken(syntaxKind), isActive);
            break;
        case SyntaxKind::MessageDirectiveKeyword:
            result = parseMessageDirective(openBraceDollarToken, takeToken(syntaxKind));
            break;
        default:
            SyntaxToken* identifier = takeToken(SyntaxKind::IdentifierToken);
            SyntaxToken* nextToken = peekToken(1);

            if (nextToken->syntaxKind() == SyntaxKind::OnDirectiveKeyword || nextToken->syntaxKind() == SyntaxKind::OffDirectiveKeyword)
                return parseSwitchDirective(openBraceDollarToken, identifier, takeToken());

            SyntaxToken* endOfDirectiveToken = parseEndOfDirective();

            if (!isAfterNonWhitespaceOnLine)
            {
                // TODO error handling
            }

            result = BadDirectiveTriviaSyntax::create(openBraceDollarToken, identifier, endOfDirectiveToken, isActive);
            break;
    }

    return result;
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseIfDirective(SyntaxToken* openBraceDollarToken,
                                                               SyntaxToken* keyword,
                                                               bool isActive) noexcept
{
    ExpressionSyntax* expression = parseExpression();
    SyntaxToken* endOfDirective = parseEndOfDirective();
    const bool isTrue = evaluateBool(expression);
    const bool isBranchTaken = isActive && isTrue;
    return IfDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, expression, endOfDirective, isActive, isBranchTaken, isTrue);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseIfDefDirective(SyntaxToken* openBraceDollarToken,
                                                                  SyntaxToken* keyword,
                                                                  bool isActive) noexcept
{
    SyntaxToken* identifier = takeToken(SyntaxKind::IdentifierToken);
    SyntaxToken* endOfDirective = parseEndOfDirective();
    return IfDefDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, identifier, endOfDirective, isActive);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseIfNDefDirective(SyntaxToken* openBraceDollarToken,
                                                                   SyntaxToken* keyword,
                                                                   bool isActive) noexcept
{
    SyntaxToken* identifier = takeToken(SyntaxKind::IdentifierToken);
    SyntaxToken* endOfDirective = parseEndOfDirective();
    return IfNDefDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, identifier, endOfDirective, isActive);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseIfEndDirective(SyntaxToken* openBraceDollarToken,
                                                                  SyntaxToken* keyword,
                                                                  bool isActive,
                                                                  bool endIsActive) noexcept
{
    SyntaxToken* endOfDirective = parseEndOfDirective();
    return IfEndDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, endOfDirective, isActive);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseElseDirective(SyntaxToken* openBraceDollarToken,
                                                                 SyntaxToken* keyword,
                                                                 bool isActive,
                                                                 bool endIsActive) noexcept
{
    SyntaxToken* endOfDirective = parseEndOfDirective();

    if (_context.hasPreviousIfOrElseIf())
    {
        const bool isBranchTaken = endIsActive && !_context.isPreviousBranchTaken();
        return ElseDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, endOfDirective, isActive, isBranchTaken);
    }
    else if (_context.hasUnfinishedRegion())
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, endOfDirective, isActive);
    }
    else if (_context.hasUnfinishedIf())
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, endOfDirective, isActive);
    }
    else
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, endOfDirective, isActive);
    }
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseElseIfDirective(SyntaxToken* openBraceDollarToken,
                                                                   SyntaxToken* keyword,
                                                                   bool isActive,
                                                                   bool endIsActive) noexcept
{
    ExpressionSyntax* expression = parseExpression();
    SyntaxToken* endOfDirective = parseEndOfDirective();

    if (_context.hasPreviousIfOrElseIf())
    {
        const bool isTrue = evaluateBool(expression);
        const bool isBranchTaken = endIsActive && isTrue && !_context.isPreviousBranchTaken();
        return ElseIfDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, expression, endOfDirective, isActive, isBranchTaken, isTrue);
    }
    else
    {
        // TODO error handling

        if (_context.hasUnfinishedRegion())
        {
            // TODO error handling
            return BadDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, endOfDirective, isActive);
        }
        else if (_context.hasUnfinishedIf())
        {
            // TODO error handling
            return BadDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, endOfDirective, isActive);
        }
        else
        {
            // TODO error handling
            return BadDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, endOfDirective, isActive);
        }
    }
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseEndIfDirective(SyntaxToken* openBraceDollarToken,
                                                                  SyntaxToken* keyword,
                                                                  bool isActive,
                                                                  bool endIsActive) noexcept
{
    SyntaxToken* endOfDirective = parseEndOfDirective();

    if (_context.hasUnfinishedIf())
        return EndIfDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, endOfDirective, isActive);
    else if (_context.hasUnfinishedRegion())
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, endOfDirective, isActive);
    }
    else
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, endOfDirective, isActive);
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

    SyntaxToken* name = takeToken(SyntaxKind::IdentifierToken);
    SyntaxToken* endOfDirective = parseEndOfDirective();

    if (keyword->syntaxKind() == SyntaxKind::DefineDirectiveKeyword)
        return DefineDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, name, endOfDirective, isActive);
    else
        return UndefDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, name, endOfDirective, isActive);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseRegionDirective(SyntaxToken* openBraceDollarToken,
                                                                   SyntaxToken* keyword,
                                                                   bool isActive) noexcept
{
    SyntaxToken* endOfDirective = parseEndOfDirective();
    return RegionDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, endOfDirective, isActive);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseEndRegionDirective(SyntaxToken* openBraceDollarToken,
                                                                      SyntaxToken* keyword,
                                                                      bool isActive) noexcept
{
    SyntaxToken* endOfDirective = parseEndOfDirective();

    if (_context.hasUnfinishedRegion())
        return EndRegionDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, endOfDirective, isActive);
    else if (_context.hasUnfinishedIf())
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, endOfDirective, isActive);
    }
    else
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, endOfDirective, isActive);
    }
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseMessageDirective(SyntaxToken* openBraceDollarToken,
                                                                    SyntaxToken* keyword) noexcept
{
    SyntaxToken* messageType{nullptr};

    if (peekToken(1)->syntaxKind() == SyntaxKind::IdentifierToken)
        messageType = takeToken();

    SyntaxToken* message = takeToken(SyntaxKind::SingleQuotationStringLiteralToken);
    SyntaxToken* endOfDirective = parseEndOfDirective();

    return MessageDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, messageType, message, endOfDirective);
}

DirectiveTriviaSyntax* DelphiDirectiveParser::parseSwitchDirective(SyntaxToken* openBraceDollarToken,
                                                                   SyntaxToken* identifier,
                                                                   SyntaxToken* onOffToken) noexcept
{
    SyntaxToken* endOfDirective = parseEndOfDirective();
    return SwitchDirectiveTriviaSyntax::create(openBraceDollarToken, identifier, onOffToken, endOfDirective);
}

SyntaxToken* DelphiDirectiveParser::parseEndOfDirective() noexcept
{
    std::vector<SyntaxNode*> skippedTokens{};

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

    SyntaxToken* endOfDirective{nullptr};

    if (currentToken()->syntaxKind() == SyntaxKind::EndOfDirectiveToken)
        endOfDirective = takeToken();
    else
    {
        auto ptrEndOfDirective = std::make_unique<SyntaxToken>(SyntaxKind::EndOfDirectiveToken);
        endOfDirective = SyntaxPool::addSyntaxToken(std::move(ptrEndOfDirective));
    }

    if (skippedTokens.size() > 0)
    {
        auto ptrSkippedTokensTrivia = std::make_unique<SkippedTokensTriviaSyntax>(SyntaxKind::SkippedTokensTrivia, std::move(skippedTokens));
        SkippedTokensTriviaSyntax* skippedTokensTrivia = static_cast<SkippedTokensTriviaSyntax*>(SyntaxPool::addSyntaxNode(std::move(ptrSkippedTokensTrivia)));
        endOfDirective->addLeadingTrivia(skippedTokensTrivia);
    }

    // TODO create skipped tokens trivia
    return endOfDirective;
}

ExpressionSyntax* DelphiDirectiveParser::parseExpression() noexcept
{
    return parseLogicalOr();
}

ExpressionSyntax* DelphiDirectiveParser::parseLogicalOr() noexcept
{
    ExpressionSyntax* leftExpression = parseLogicalAnd();

    while (currentToken()->syntaxKind() == SyntaxKind::OrKeyword)
    {
        SyntaxToken* operatorToken = takeToken();
        ExpressionSyntax* rightExpression = parseLogicalAnd();
        leftExpression = BinaryExpressionSyntax::create(SyntaxKind::LogicalOrExpression, leftExpression, operatorToken, rightExpression);
    }

    return leftExpression;
}

ExpressionSyntax* DelphiDirectiveParser::parseLogicalAnd() noexcept
{
    ExpressionSyntax* leftExpression = parseEquality();

    while (currentToken()->syntaxKind() == SyntaxKind::AndKeyword)
    {
        SyntaxToken* operatorToken = takeToken();
        ExpressionSyntax* rightExpression = parseEquality();
        leftExpression = BinaryExpressionSyntax::create(SyntaxKind::LogicalAndExpression, leftExpression, operatorToken, rightExpression);
    }

    return leftExpression;
}

ExpressionSyntax* DelphiDirectiveParser::parseEquality() noexcept
{
    ExpressionSyntax* leftExpression = parseLogicalNot();
    SyntaxKind currentSyntaxKind = currentToken()->syntaxKind();

    while (DelphiSyntaxFacts::isComparisonSyntaxKind(currentSyntaxKind))
    {
        SyntaxToken* operatorToken = takeToken();
        ExpressionSyntax* rightExpression = parseEquality();
        SyntaxKind expressionKind = DelphiSyntaxFacts::binaryExpressionKind(operatorToken->syntaxKind());
        leftExpression = BinaryExpressionSyntax::create(expressionKind, leftExpression, operatorToken, rightExpression);
        currentSyntaxKind = currentToken()->syntaxKind();
    }

    return leftExpression;
}

ExpressionSyntax* DelphiDirectiveParser::parseLogicalNot() noexcept
{
    if (currentToken()->syntaxKind() == SyntaxKind::NotKeyword)
    {
        SyntaxToken* operatorToken = takeToken();
        return PrefixUnaryExpressionSyntax::create(SyntaxKind::LogicalNotExpression, operatorToken, parseLogicalNot());
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
            SyntaxToken* openParenthesisToken = takeToken();
            ExpressionSyntax* expression = parseExpression();
            SyntaxToken* closeParenthesisToken = takeToken(SyntaxKind::CloseParenthesisToken);
            return ParenthesizedExpressionSyntax::create(openParenthesisToken, expression, closeParenthesisToken);
        }
        case SyntaxKind::IdentifierToken:
        {
            SyntaxToken* identifier = takeToken();

            if (peekToken(1)->syntaxKind() == SyntaxKind::OpenParenthesisToken)
                return parseCallExpression(identifier);

            return IdentifierNameExpressionSyntax::create(identifier);
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
    SyntaxToken* openParenthesisToken = takeToken(SyntaxKind::OpenParenthesisToken);
    ExpressionSyntax* expression = parseExpression();
    SyntaxToken* closeParenthesisToken = takeToken(SyntaxKind::CloseParenthesisToken);
    return CallExpressionSyntax::create(SyntaxKind::CallExpression, identifier, openParenthesisToken, expression, closeParenthesisToken);
}

bool DelphiDirectiveParser::evaluateBool(ExpressionSyntax* expression) const noexcept
{
    switch (expression->syntaxKind())
    {
        case SyntaxKind::LogicalNotExpression:
            return !evaluateBool(static_cast<PrefixUnaryExpressionSyntax*>(expression)->operandExpression());
        case SyntaxKind::LogicalOrExpression:
        case SyntaxKind::LogicalAndExpression:
        case SyntaxKind::EqualsExpression:
        case SyntaxKind::NotEqualsExpression:
        {
            BinaryExpressionSyntax* binaryExpression = static_cast<BinaryExpressionSyntax*>(expression);
            assert(binaryExpression != nullptr);

            switch (binaryExpression->syntaxKind())
            {
                case SyntaxKind::LogicalOrExpression:
                    return evaluateBool(binaryExpression->leftExpression()) || evaluateBool(binaryExpression->rightExpression());
                case SyntaxKind::LogicalAndExpression:
                    return evaluateBool(binaryExpression->leftExpression()) && evaluateBool(binaryExpression->rightExpression());
                case SyntaxKind::EqualsExpression:
                    return evaluateBool(binaryExpression->leftExpression()) == evaluateBool(binaryExpression->rightExpression());
                case SyntaxKind::NotEqualsExpression:
                    return evaluateBool(binaryExpression->leftExpression()) != evaluateBool(binaryExpression->rightExpression());
            }

            break;
        }
        case SyntaxKind::ParenthesizedExpression:
            return evaluateBool(static_cast<ParenthesizedExpressionSyntax*>(expression));
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
