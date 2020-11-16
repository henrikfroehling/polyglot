#include "polyglot/CodeAnalysis/Delphi/DelphiDirectiveParser.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/ExpressionSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Expressions/BinaryExpressionSyntax.hpp"
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
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/IfDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/RegionDirectiveTriviaSyntax.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Trivia/UndefDirectiveTriviaSyntax.hpp"
#include <cassert>
#include <vector>

namespace polyglot::CodeAnalysis
{

DelphiDirectiveParser::DelphiDirectiveParser(std::shared_ptr<Lexer> lexer,
                                             const DirectiveStack& context,
                                             std::shared_ptr<SyntaxFacts> syntaxFacts) noexcept
    : DirectiveParser{lexer, context, syntaxFacts}
{}

SyntaxNodePtr DelphiDirectiveParser::parseDirective(bool isActive,
                                                    bool endIsActive,
                                                    bool isFirstAfterTokenInFile,
                                                    bool isAfterNonWhitespaceOnLine) noexcept
{
    SyntaxTokenPtr openBraceDollarToken = takeToken(SyntaxKind::OpenBraceDollarToken);
    assert(openBraceDollarToken != nullptr);

    if (isAfterNonWhitespaceOnLine)
    {
        // TODO error handling
    }

    SyntaxNodePtr result{ nullptr };
    SyntaxKind contextualKind = currentToken()->contextualKind();

    switch (contextualKind)
    {
        case SyntaxKind::IfDirectiveKeyword:
            result = parseIfDirective(std::move(openBraceDollarToken), takeContextualToken(contextualKind), isActive);
            break;
        case SyntaxKind::ElseDirectiveKeyword:
            result = parseElseDirective(std::move(openBraceDollarToken), takeContextualToken(contextualKind), isActive, endIsActive);
            break;
        case SyntaxKind::ElseIfDirectiveKeyword:
            result = parseElseIfDirective(std::move(openBraceDollarToken), takeContextualToken(contextualKind), isActive, endIsActive);
            break;
        case SyntaxKind::EndIfDirectiveKeyword:
            result = parseEndIfDirective(std::move(openBraceDollarToken), takeContextualToken(contextualKind), isActive, endIsActive);
            break;
        case SyntaxKind::DefineDirectiveKeyword:
        case SyntaxKind::UndefDirectiveKeyword:
            result = parseDefineOrUndefDirective(std::move(openBraceDollarToken), takeContextualToken(contextualKind), isActive, endIsActive);
            break;
        case SyntaxKind::RegionDirectiveKeyword:
            result = parseRegionDirective(std::move(openBraceDollarToken), takeContextualToken(contextualKind), isActive);
            break;
        case SyntaxKind::EndRegionDirectiveKeyword:
            result = parseEndRegionDirective(std::move(openBraceDollarToken), takeContextualToken(contextualKind), isActive);
            break;
        default:
            SyntaxTokenPtr identifierToken = takeToken(SyntaxKind::IdentifierToken);
            SyntaxTokenPtr endOfDirectiveToken = parseEndOfDirective();

            if (!isAfterNonWhitespaceOnLine)
            {
                // TODO error handling
            }

            result = BadDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(identifierToken), std::move(endOfDirectiveToken), isActive);
            break;
    }

    return std::move(result);
}

DirectiveTriviaSyntaxPtr DelphiDirectiveParser::parseIfDirective(SyntaxTokenPtr openBraceDollarToken,
                                                                 SyntaxTokenPtr keyword,
                                                                 bool isActive) noexcept
{
    ExpressionSyntaxPtr expression = parseExpression();
    SyntaxTokenPtr endOfDirective = parseEndOfDirective();
    const bool isTrue = evaluateBool(expression);
    const bool isBranchTaken = isActive && isTrue;

    return IfDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword), std::move(expression),
                                           std::move(endOfDirective), isActive, isBranchTaken, isTrue);
}

DirectiveTriviaSyntaxPtr DelphiDirectiveParser::parseElseDirective(SyntaxTokenPtr openBraceDollarToken,
                                                                   SyntaxTokenPtr keyword,
                                                                   bool isActive,
                                                                   bool endIsActive) noexcept
{
    SyntaxTokenPtr endOfDirective = parseEndOfDirective();

    if (_context.hasPreviousIfOrElseIf())
    {
        const bool isBranchTaken = endIsActive && !_context.isPreviousBranchTaken();

        return ElseDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword),
                                                 std::move(endOfDirective), isActive, isBranchTaken);
    }
    else if (_context.hasUnfinishedRegion())
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
    }
    else if (_context.hasUnfinishedIf())
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
    }
    else
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
    }
}

DirectiveTriviaSyntaxPtr DelphiDirectiveParser::parseElseIfDirective(SyntaxTokenPtr openBraceDollarToken,
                                                                     SyntaxTokenPtr keyword,
                                                                     bool isActive,
                                                                     bool endIsActive) noexcept
{
    ExpressionSyntaxPtr expression = parseExpression();
    SyntaxTokenPtr endOfDirective = parseEndOfDirective();

    if (_context.hasPreviousIfOrElseIf())
    {
        const bool isTrue = evaluateBool(expression);
        const bool isBranchTaken = endIsActive && isTrue && !_context.isPreviousBranchTaken();

        return ElseIfDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword), std::move(expression),
                                                   std::move(endOfDirective), isActive, isBranchTaken, isTrue);
    }
    else
    {
        // TODO error handling

        if (_context.hasUnfinishedRegion())
        {
            // TODO error handling
            return BadDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
        }
        else if (_context.hasUnfinishedIf())
        {
            // TODO error handling
            return BadDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
        }
        else
        {
            // TODO error handling
            return BadDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
        }
    }
}

DirectiveTriviaSyntaxPtr DelphiDirectiveParser::parseEndIfDirective(SyntaxTokenPtr openBraceDollarToken,
                                                                    SyntaxTokenPtr keyword,
                                                                    bool isActive,
                                                                    bool endIsActive) noexcept
{
    SyntaxTokenPtr endOfDirective = parseEndOfDirective();

    if (_context.hasUnfinishedIf())
    {
        return EndIfDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
    }
    else if (_context.hasUnfinishedRegion())
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
    }
    else
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
    }
}

DirectiveTriviaSyntaxPtr DelphiDirectiveParser::parseDefineOrUndefDirective(SyntaxTokenPtr openBraceDollarToken,
                                                                            SyntaxTokenPtr keyword,
                                                                            bool isActive,
                                                                            bool isFollowingToken) noexcept
{
    if (isFollowingToken)
    {
        // TODO error handling
    }

    SyntaxTokenPtr name = takeToken(SyntaxKind::IdentifierToken);
    SyntaxTokenPtr endOfDirective = parseEndOfDirective();

    if (keyword->syntaxKind() == SyntaxKind::DefineDirectiveKeyword)
        return DefineDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword), std::move(name), std::move(endOfDirective), isActive);
    else
        return UndefDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword), std::move(name), std::move(endOfDirective), isActive);
}

DirectiveTriviaSyntaxPtr DelphiDirectiveParser::parseRegionDirective(SyntaxTokenPtr openBraceDollarToken,
                                                                     SyntaxTokenPtr keyword,
                                                                     bool isActive) noexcept
{
    SyntaxTokenPtr endOfDirective = parseEndOfDirective();
    return RegionDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
}

DirectiveTriviaSyntaxPtr DelphiDirectiveParser::parseEndRegionDirective(SyntaxTokenPtr openBraceDollarToken,
                                                                        SyntaxTokenPtr keyword,
                                                                        bool isActive) noexcept
{
    SyntaxTokenPtr endOfDirective = parseEndOfDirective();

    if (_context.hasUnfinishedRegion())
    {
        return EndRegionDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
    }
    else if (_context.hasUnfinishedIf())
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
    }
    else
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
    }
}

SyntaxTokenPtr DelphiDirectiveParser::parseEndOfDirective() noexcept
{
    std::vector<SyntaxTokenPtr> skippedTokens{};

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

    SyntaxTokenPtr endOfDirective = currentToken()->syntaxKind() == SyntaxKind::EndOfDirectiveToken
        ? takeToken()
        : std::make_shared<SyntaxToken>(SyntaxKind::EndOfDirectiveToken);

    // TODO create skipped tokens trivia

    return std::move(endOfDirective);
}

ExpressionSyntaxPtr DelphiDirectiveParser::parseExpression() noexcept
{
    return parseLogicalOr();
}

ExpressionSyntaxPtr DelphiDirectiveParser::parseLogicalOr() noexcept
{
    ExpressionSyntaxPtr leftExpression = parseLogicalAnd();

    while (currentToken()->syntaxKind() == SyntaxKind::OrKeyword)
    {
        SyntaxTokenPtr operatorToken = takeToken();
        ExpressionSyntaxPtr rightExpression = parseLogicalAnd();

        leftExpression = BinaryExpressionSyntax::Create(SyntaxKind::LogicalOrExpression, std::move(leftExpression),
                                                        std::move(operatorToken), std::move(rightExpression));
    }

    return std::move(leftExpression);
}

ExpressionSyntaxPtr DelphiDirectiveParser::parseLogicalAnd() noexcept
{
    ExpressionSyntaxPtr leftExpression = parseEquality();

    while (currentToken()->syntaxKind() == SyntaxKind::AndKeyword)
    {
        SyntaxTokenPtr operatorToken = takeToken();
        ExpressionSyntaxPtr rightExpression = parseEquality();

        leftExpression = BinaryExpressionSyntax::Create(SyntaxKind::LogicalAndExpression, std::move(leftExpression),
                                                        std::move(operatorToken), std::move(rightExpression));
    }

    return std::move(leftExpression);
}

ExpressionSyntaxPtr DelphiDirectiveParser::parseEquality() noexcept
{
    ExpressionSyntaxPtr leftExpression = parseLogicalNot();

    while (currentToken()->syntaxKind() == SyntaxKind::EqualToken
           || currentToken()->syntaxKind() == SyntaxKind::LessThanGreaterThanToken)
    {
        SyntaxTokenPtr operatorToken = takeToken();
        ExpressionSyntaxPtr rightExpression = parseEquality();
        const SyntaxKind expressionKind = _ptrSyntaxFacts->binaryExpressionKind(operatorToken->syntaxKind());

        leftExpression = BinaryExpressionSyntax::Create(expressionKind, std::move(leftExpression),
                                                        std::move(operatorToken), std::move(rightExpression));
    }

    return std::move(leftExpression);
}

ExpressionSyntaxPtr DelphiDirectiveParser::parseLogicalNot() noexcept
{
    if (currentToken()->syntaxKind() == SyntaxKind::ExclamationMarkToken)
    {
        SyntaxTokenPtr operatorToken = takeToken();
        return PrefixUnaryExpressionSyntax::Create(SyntaxKind::LogicalNotExpression, std::move(operatorToken), parseLogicalNot());
    }

    return parsePrimary();
}

ExpressionSyntaxPtr DelphiDirectiveParser::parsePrimary() noexcept
{
    SyntaxKind syntaxKind = currentToken()->syntaxKind();

    switch (syntaxKind)
    {
        case SyntaxKind::OpenParenthesisToken:
        {
            SyntaxTokenPtr openParenthesisToken = takeToken();
            ExpressionSyntaxPtr expression = parseExpression();
            SyntaxTokenPtr closeParenthesisToken = takeToken(SyntaxKind::CloseParenthesisToken);
            return ParenthesizedExpressionSyntax::Create(std::move(openParenthesisToken), std::move(expression), std::move(closeParenthesisToken));
        }
        case SyntaxKind::IdentifierToken:
            return IdentifierNameExpressionSyntax::Create(takeToken());
        case SyntaxKind::TrueKeyword:
        case SyntaxKind::FalseKeyword:
            return LiteralExpressionSyntax::Create(_ptrSyntaxFacts->literalExpressionKind(syntaxKind), takeToken());
        default:
            return IdentifierNameExpressionSyntax::Create(takeToken(SyntaxKind::IdentifierToken));
    }

    return nullptr;
}

bool DelphiDirectiveParser::evaluateBool(const ExpressionSyntaxPtr& expression) const noexcept
{
    switch (expression->syntaxKind())
    {
        case SyntaxKind::LogicalNotExpression:
            return !evaluateBool(std::dynamic_pointer_cast<PrefixUnaryExpressionSyntax>(expression)->operandExpression());
        case SyntaxKind::LogicalOrExpression:
        {
            BinaryExpressionSyntaxPtr binaryExpression = std::dynamic_pointer_cast<BinaryExpressionSyntax>(expression);
            return evaluateBool(binaryExpression->leftExpression()) || evaluateBool(binaryExpression->rightExpression());
        }
        case SyntaxKind::LogicalAndExpression:
        {
            BinaryExpressionSyntaxPtr binaryExpression = std::dynamic_pointer_cast<BinaryExpressionSyntax>(expression);
            return evaluateBool(binaryExpression->leftExpression()) && evaluateBool(binaryExpression->rightExpression());
        }
        case SyntaxKind::EqualsExpression:
        {
            BinaryExpressionSyntaxPtr binaryExpression = std::dynamic_pointer_cast<BinaryExpressionSyntax>(expression);
            return evaluateBool(binaryExpression->leftExpression()) == evaluateBool(binaryExpression->rightExpression());
        }
        case SyntaxKind::NotEqualsExpression:
        {
            BinaryExpressionSyntaxPtr binaryExpression = std::dynamic_pointer_cast<BinaryExpressionSyntax>(expression);
            return evaluateBool(binaryExpression->leftExpression()) != evaluateBool(binaryExpression->rightExpression());
        }
        case SyntaxKind::ParenthesizedExpression:
            return evaluateBool(std::dynamic_pointer_cast<ParenthesizedExpressionSyntax>(expression));
        case SyntaxKind::TrueLiteralExpression:
        case SyntaxKind::FalseLiteralExpression:
            return std::dynamic_pointer_cast<LiteralExpressionSyntax>(expression)->token()->value();
        case SyntaxKind::IdentifierNameExpression:
            return isDefined(std::dynamic_pointer_cast<IdentifierNameExpressionSyntax>(expression)->identifier()->text());
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
        case DefineState::Undefined:
        case DefineState::Unspecified:
        default:
            return false;
    }
}

} // end namespace polyglot::CodeAnalysis
