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

DelphiDirectiveParser::DelphiDirectiveParser(SharedPtr<Lexer> lexer,
                                             const DirectiveStack& context,
                                             SharedPtr<SyntaxFacts> syntaxFacts) noexcept
    : DirectiveParser{lexer, context, syntaxFacts}
{}

SharedPtr<SyntaxNode> DelphiDirectiveParser::parseDirective(bool isActive,
                                                            bool endIsActive,
                                                            bool isFirstAfterTokenInFile,
                                                            bool isAfterNonWhitespaceOnLine) noexcept
{
    SharedPtr<SyntaxToken> openBraceDollarToken = takeToken(SyntaxKind::OpenBraceDollarToken);
    assert(openBraceDollarToken != nullptr);

    if (isAfterNonWhitespaceOnLine)
    {
        // TODO error handling
    }

    SharedPtr<SyntaxNode> result{nullptr};
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
            SharedPtr<SyntaxToken> identifierToken = takeToken(SyntaxKind::IdentifierToken);
            SharedPtr<SyntaxToken> endOfDirectiveToken = parseEndOfDirective();

            if (!isAfterNonWhitespaceOnLine)
            {
                // TODO error handling
            }

            result = BadDirectiveTriviaSyntax::create(std::move(openBraceDollarToken), std::move(identifierToken), std::move(endOfDirectiveToken), isActive);
            break;
    }

    return std::move(result);
}

SharedPtr<DirectiveTriviaSyntax> DelphiDirectiveParser::parseIfDirective(SharedPtr<SyntaxToken> openBraceDollarToken,
                                                                         SharedPtr<SyntaxToken> keyword,
                                                                         bool isActive) noexcept
{
    SharedPtr<ExpressionSyntax> expression = parseExpression();
    SharedPtr<SyntaxToken> endOfDirective = parseEndOfDirective();
    const bool isTrue = evaluateBool(expression);
    const bool isBranchTaken = isActive && isTrue;

    return IfDirectiveTriviaSyntax::create(std::move(openBraceDollarToken), std::move(keyword), std::move(expression),
                                           std::move(endOfDirective), isActive, isBranchTaken, isTrue);
}

SharedPtr<DirectiveTriviaSyntax> DelphiDirectiveParser::parseElseDirective(SharedPtr<SyntaxToken> openBraceDollarToken,
                                                                           SharedPtr<SyntaxToken> keyword,
                                                                           bool isActive,
                                                                           bool endIsActive) noexcept
{
    SharedPtr<SyntaxToken> endOfDirective = parseEndOfDirective();

    if (_context.hasPreviousIfOrElseIf())
    {
        const bool isBranchTaken = endIsActive && !_context.isPreviousBranchTaken();

        return ElseDirectiveTriviaSyntax::create(std::move(openBraceDollarToken), std::move(keyword),
                                                 std::move(endOfDirective), isActive, isBranchTaken);
    }
    else if (_context.hasUnfinishedRegion())
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
    }
    else if (_context.hasUnfinishedIf())
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
    }
    else
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
    }
}

SharedPtr<DirectiveTriviaSyntax> DelphiDirectiveParser::parseElseIfDirective(SharedPtr<SyntaxToken> openBraceDollarToken,
                                                                             SharedPtr<SyntaxToken> keyword,
                                                                             bool isActive,
                                                                             bool endIsActive) noexcept
{
    SharedPtr<ExpressionSyntax> expression = parseExpression();
    SharedPtr<SyntaxToken> endOfDirective = parseEndOfDirective();

    if (_context.hasPreviousIfOrElseIf())
    {
        const bool isTrue = evaluateBool(expression);
        const bool isBranchTaken = endIsActive && isTrue && !_context.isPreviousBranchTaken();

        return ElseIfDirectiveTriviaSyntax::create(std::move(openBraceDollarToken), std::move(keyword), std::move(expression),
                                                   std::move(endOfDirective), isActive, isBranchTaken, isTrue);
    }
    else
    {
        // TODO error handling

        if (_context.hasUnfinishedRegion())
        {
            // TODO error handling
            return BadDirectiveTriviaSyntax::create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
        }
        else if (_context.hasUnfinishedIf())
        {
            // TODO error handling
            return BadDirectiveTriviaSyntax::create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
        }
        else
        {
            // TODO error handling
            return BadDirectiveTriviaSyntax::create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
        }
    }
}

SharedPtr<DirectiveTriviaSyntax> DelphiDirectiveParser::parseEndIfDirective(SharedPtr<SyntaxToken> openBraceDollarToken,
                                                                            SharedPtr<SyntaxToken> keyword,
                                                                            bool isActive,
                                                                            bool endIsActive) noexcept
{
    SharedPtr<SyntaxToken> endOfDirective = parseEndOfDirective();

    if (_context.hasUnfinishedIf())
    {
        return EndIfDirectiveTriviaSyntax::create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
    }
    else if (_context.hasUnfinishedRegion())
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
    }
    else
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
    }
}

SharedPtr<DirectiveTriviaSyntax> DelphiDirectiveParser::parseDefineOrUndefDirective(SharedPtr<SyntaxToken> openBraceDollarToken,
                                                                                    SharedPtr<SyntaxToken> keyword,
                                                                                    bool isActive,
                                                                                    bool isFollowingToken) noexcept
{
    if (isFollowingToken)
    {
        // TODO error handling
    }

    SharedPtr<SyntaxToken> name = takeToken(SyntaxKind::IdentifierToken);
    SharedPtr<SyntaxToken> endOfDirective = parseEndOfDirective();

    if (keyword->syntaxKind() == SyntaxKind::DefineDirectiveKeyword)
        return DefineDirectiveTriviaSyntax::create(std::move(openBraceDollarToken), std::move(keyword), std::move(name), std::move(endOfDirective), isActive);
    else
        return UndefDirectiveTriviaSyntax::create(std::move(openBraceDollarToken), std::move(keyword), std::move(name), std::move(endOfDirective), isActive);
}

SharedPtr<DirectiveTriviaSyntax> DelphiDirectiveParser::parseRegionDirective(SharedPtr<SyntaxToken> openBraceDollarToken,
                                                                             SharedPtr<SyntaxToken> keyword,
                                                                             bool isActive) noexcept
{
    SharedPtr<SyntaxToken> endOfDirective = parseEndOfDirective();
    return RegionDirectiveTriviaSyntax::create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
}

SharedPtr<DirectiveTriviaSyntax> DelphiDirectiveParser::parseEndRegionDirective(SharedPtr<SyntaxToken> openBraceDollarToken,
                                                                                SharedPtr<SyntaxToken> keyword,
                                                                                bool isActive) noexcept
{
    SharedPtr<SyntaxToken> endOfDirective = parseEndOfDirective();

    if (_context.hasUnfinishedRegion())
    {
        return EndRegionDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
    }
    else if (_context.hasUnfinishedIf())
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
    }
    else
    {
        // TODO error handling
        return BadDirectiveTriviaSyntax::create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
    }
}

SharedPtr<SyntaxToken> DelphiDirectiveParser::parseEndOfDirective() noexcept
{
    std::vector<SharedPtr<SyntaxToken>> skippedTokens{};

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

    SharedPtr<SyntaxToken> endOfDirective = currentToken()->syntaxKind() == SyntaxKind::EndOfDirectiveToken
        ? takeToken()
        : std::make_shared<SyntaxToken>(SyntaxKind::EndOfDirectiveToken);

    // TODO create skipped tokens trivia

    return std::move(endOfDirective);
}

SharedPtr<ExpressionSyntax> DelphiDirectiveParser::parseExpression() noexcept
{
    return parseLogicalOr();
}

SharedPtr<ExpressionSyntax> DelphiDirectiveParser::parseLogicalOr() noexcept
{
    SharedPtr<ExpressionSyntax> leftExpression = parseLogicalAnd();

    while (currentToken()->syntaxKind() == SyntaxKind::OrKeyword)
    {
        SharedPtr<SyntaxToken> operatorToken = takeToken();
        SharedPtr<ExpressionSyntax> rightExpression = parseLogicalAnd();

        leftExpression = BinaryExpressionSyntax::create(SyntaxKind::LogicalOrExpression, std::move(leftExpression),
                                                        std::move(operatorToken), std::move(rightExpression));
    }

    return std::move(leftExpression);
}

SharedPtr<ExpressionSyntax> DelphiDirectiveParser::parseLogicalAnd() noexcept
{
    SharedPtr<ExpressionSyntax> leftExpression = parseEquality();

    while (currentToken()->syntaxKind() == SyntaxKind::AndKeyword)
    {
        SharedPtr<SyntaxToken> operatorToken = takeToken();
        SharedPtr<ExpressionSyntax> rightExpression = parseEquality();

        leftExpression = BinaryExpressionSyntax::create(SyntaxKind::LogicalAndExpression, std::move(leftExpression),
                                                        std::move(operatorToken), std::move(rightExpression));
    }

    return std::move(leftExpression);
}

SharedPtr<ExpressionSyntax> DelphiDirectiveParser::parseEquality() noexcept
{
    SharedPtr<ExpressionSyntax> leftExpression = parseLogicalNot();

    while (currentToken()->syntaxKind() == SyntaxKind::EqualToken
           || currentToken()->syntaxKind() == SyntaxKind::LessThanGreaterThanToken)
    {
        SharedPtr<SyntaxToken> operatorToken = takeToken();
        SharedPtr<ExpressionSyntax> rightExpression = parseEquality();
        const SyntaxKind expressionKind = _ptrSyntaxFacts->binaryExpressionKind(operatorToken->syntaxKind());

        leftExpression = BinaryExpressionSyntax::create(expressionKind, std::move(leftExpression),
                                                        std::move(operatorToken), std::move(rightExpression));
    }

    return std::move(leftExpression);
}

SharedPtr<ExpressionSyntax> DelphiDirectiveParser::parseLogicalNot() noexcept
{
    if (currentToken()->syntaxKind() == SyntaxKind::ExclamationMarkToken)
    {
        SharedPtr<SyntaxToken> operatorToken = takeToken();
        return PrefixUnaryExpressionSyntax::create(SyntaxKind::LogicalNotExpression, std::move(operatorToken), parseLogicalNot());
    }

    return parsePrimary();
}

SharedPtr<ExpressionSyntax> DelphiDirectiveParser::parsePrimary() noexcept
{
    SyntaxKind syntaxKind = currentToken()->syntaxKind();

    switch (syntaxKind)
    {
        case SyntaxKind::OpenParenthesisToken:
        {
            SharedPtr<SyntaxToken> openParenthesisToken = takeToken();
            SharedPtr<ExpressionSyntax> expression = parseExpression();
            SharedPtr<SyntaxToken> closeParenthesisToken = takeToken(SyntaxKind::CloseParenthesisToken);
            return ParenthesizedExpressionSyntax::create(std::move(openParenthesisToken), std::move(expression), std::move(closeParenthesisToken));
        }
        case SyntaxKind::IdentifierToken:
            return IdentifierNameExpressionSyntax::create(takeToken());
        case SyntaxKind::TrueKeyword:
        case SyntaxKind::FalseKeyword:
            return LiteralExpressionSyntax::create(_ptrSyntaxFacts->literalExpressionKind(syntaxKind), takeToken());
        default:
            return IdentifierNameExpressionSyntax::create(takeToken(SyntaxKind::IdentifierToken));
    }

    return nullptr;
}

bool DelphiDirectiveParser::evaluateBool(const SharedPtr<ExpressionSyntax>& expression) const noexcept
{
    switch (expression->syntaxKind())
    {
        case SyntaxKind::LogicalNotExpression:
            return !evaluateBool(std::dynamic_pointer_cast<PrefixUnaryExpressionSyntax>(expression)->operandExpression());
        case SyntaxKind::LogicalOrExpression:
        case SyntaxKind::LogicalAndExpression:
        case SyntaxKind::EqualsExpression:
        case SyntaxKind::NotEqualsExpression:
        {
            SharedPtr<BinaryExpressionSyntax> binaryExpression = std::dynamic_pointer_cast<BinaryExpressionSyntax>(expression);
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
