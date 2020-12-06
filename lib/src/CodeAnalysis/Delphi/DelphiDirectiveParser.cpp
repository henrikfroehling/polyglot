#include "polyglot/CodeAnalysis/Delphi/DelphiDirectiveParser.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
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

Ptr<SyntaxNode> DelphiDirectiveParser::parseDirective(bool isActive,
                                                      bool endIsActive,
                                                      bool isFirstAfterTokenInFile,
                                                      bool isAfterNonWhitespaceOnLine) noexcept
{
    Ptr<SyntaxToken> openBraceDollarToken = takeToken(SyntaxKind::OpenBraceDollarToken);
    assert(openBraceDollarToken != nullptr);

    if (isAfterNonWhitespaceOnLine)
    {
        // TODO error handling
    }

    Ptr<SyntaxNode> result{nullptr};
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
            Ptr<SyntaxToken> identifierToken = takeToken(SyntaxKind::IdentifierToken);
            Ptr<SyntaxToken> endOfDirectiveToken = parseEndOfDirective();

            if (!isAfterNonWhitespaceOnLine)
            {
                // TODO error handling
            }

            result = BadDirectiveTriviaSyntax::create(openBraceDollarToken, identifierToken, endOfDirectiveToken, isActive);
            break;
    }

    return std::move(result);
}

Ptr<DirectiveTriviaSyntax> DelphiDirectiveParser::parseIfDirective(Ptr<SyntaxToken> openBraceDollarToken,
                                                                   Ptr<SyntaxToken> keyword,
                                                                   bool isActive) noexcept
{
    Ptr<ExpressionSyntax> expression = parseExpression();
    Ptr<SyntaxToken> endOfDirective = parseEndOfDirective();
    const bool isTrue = evaluateBool(expression);
    const bool isBranchTaken = isActive && isTrue;
    return IfDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, expression, endOfDirective, isActive, isBranchTaken, isTrue);
}

Ptr<DirectiveTriviaSyntax> DelphiDirectiveParser::parseElseDirective(Ptr<SyntaxToken> openBraceDollarToken,
                                                                     Ptr<SyntaxToken> keyword,
                                                                     bool isActive,
                                                                     bool endIsActive) noexcept
{
    Ptr<SyntaxToken> endOfDirective = parseEndOfDirective();

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

Ptr<DirectiveTriviaSyntax> DelphiDirectiveParser::parseElseIfDirective(Ptr<SyntaxToken> openBraceDollarToken,
                                                                       Ptr<SyntaxToken> keyword,
                                                                       bool isActive,
                                                                       bool endIsActive) noexcept
{
    Ptr<ExpressionSyntax> expression = parseExpression();
    Ptr<SyntaxToken> endOfDirective = parseEndOfDirective();

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

Ptr<DirectiveTriviaSyntax> DelphiDirectiveParser::parseEndIfDirective(Ptr<SyntaxToken> openBraceDollarToken,
                                                                      Ptr<SyntaxToken> keyword,
                                                                      bool isActive,
                                                                      bool endIsActive) noexcept
{
    Ptr<SyntaxToken> endOfDirective = parseEndOfDirective();

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

Ptr<DirectiveTriviaSyntax> DelphiDirectiveParser::parseDefineOrUndefDirective(Ptr<SyntaxToken> openBraceDollarToken,
                                                                              Ptr<SyntaxToken> keyword,
                                                                              bool isActive,
                                                                              bool isFollowingToken) noexcept
{
    if (isFollowingToken)
    {
        // TODO error handling
    }

    Ptr<SyntaxToken> name = takeToken(SyntaxKind::IdentifierToken);
    Ptr<SyntaxToken> endOfDirective = parseEndOfDirective();

    if (keyword->syntaxKind() == SyntaxKind::DefineDirectiveKeyword)
        return DefineDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, name, endOfDirective, isActive);
    else
        return UndefDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, name, endOfDirective, isActive);
}

Ptr<DirectiveTriviaSyntax> DelphiDirectiveParser::parseRegionDirective(Ptr<SyntaxToken> openBraceDollarToken,
                                                                       Ptr<SyntaxToken> keyword,
                                                                       bool isActive) noexcept
{
    Ptr<SyntaxToken> endOfDirective = parseEndOfDirective();
    return RegionDirectiveTriviaSyntax::create(openBraceDollarToken, keyword, endOfDirective, isActive);
}

Ptr<DirectiveTriviaSyntax> DelphiDirectiveParser::parseEndRegionDirective(Ptr<SyntaxToken> openBraceDollarToken,
                                                                          Ptr<SyntaxToken> keyword,
                                                                          bool isActive) noexcept
{
    Ptr<SyntaxToken> endOfDirective = parseEndOfDirective();

    if (_context.hasUnfinishedRegion())
        return EndRegionDirectiveTriviaSyntax::Create(openBraceDollarToken, keyword, endOfDirective, isActive);
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

Ptr<SyntaxToken> DelphiDirectiveParser::parseEndOfDirective() noexcept
{
    std::vector<Ptr<SyntaxToken>> skippedTokens{};

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

    Ptr<SyntaxToken> endOfDirective{nullptr};

    if (currentToken()->syntaxKind() == SyntaxKind::EndOfDirectiveToken)
        endOfDirective = takeToken();
    else
    {
        auto ptrEndOfDirective = std::make_unique<SyntaxToken>(SyntaxKind::EndOfDirectiveToken);
        endOfDirective = SyntaxPool::addSyntaxToken(std::move(ptrEndOfDirective));
    }

    // TODO create skipped tokens trivia
    return endOfDirective;
}

Ptr<ExpressionSyntax> DelphiDirectiveParser::parseExpression() noexcept
{
    return parseLogicalOr();
}

Ptr<ExpressionSyntax> DelphiDirectiveParser::parseLogicalOr() noexcept
{
    Ptr<ExpressionSyntax> leftExpression = parseLogicalAnd();

    while (currentToken()->syntaxKind() == SyntaxKind::OrKeyword)
    {
        Ptr<SyntaxToken> operatorToken = takeToken();
        Ptr<ExpressionSyntax> rightExpression = parseLogicalAnd();
        leftExpression = BinaryExpressionSyntax::create(SyntaxKind::LogicalOrExpression, leftExpression, operatorToken, rightExpression);
    }

    return leftExpression;
}

Ptr<ExpressionSyntax> DelphiDirectiveParser::parseLogicalAnd() noexcept
{
    Ptr<ExpressionSyntax> leftExpression = parseEquality();

    while (currentToken()->syntaxKind() == SyntaxKind::AndKeyword)
    {
        Ptr<SyntaxToken> operatorToken = takeToken();
        Ptr<ExpressionSyntax> rightExpression = parseEquality();
        leftExpression = BinaryExpressionSyntax::create(SyntaxKind::LogicalAndExpression, leftExpression, operatorToken, rightExpression);
    }

    return leftExpression;
}

Ptr<ExpressionSyntax> DelphiDirectiveParser::parseEquality() noexcept
{
    Ptr<ExpressionSyntax> leftExpression = parseLogicalNot();

    while (currentToken()->syntaxKind() == SyntaxKind::EqualToken
           || currentToken()->syntaxKind() == SyntaxKind::LessThanGreaterThanToken)
    {
        Ptr<SyntaxToken> operatorToken = takeToken();
        Ptr<ExpressionSyntax> rightExpression = parseEquality();
        const SyntaxKind expressionKind = _ptrSyntaxFacts->binaryExpressionKind(operatorToken->syntaxKind());
        leftExpression = BinaryExpressionSyntax::create(expressionKind, leftExpression, operatorToken, rightExpression);
    }

    return leftExpression;
}

Ptr<ExpressionSyntax> DelphiDirectiveParser::parseLogicalNot() noexcept
{
    if (currentToken()->syntaxKind() == SyntaxKind::ExclamationMarkToken)
    {
        Ptr<SyntaxToken> operatorToken = takeToken();
        return PrefixUnaryExpressionSyntax::create(SyntaxKind::LogicalNotExpression, operatorToken, parseLogicalNot());
    }

    return parsePrimary();
}

Ptr<ExpressionSyntax> DelphiDirectiveParser::parsePrimary() noexcept
{
    SyntaxKind syntaxKind = currentToken()->syntaxKind();

    switch (syntaxKind)
    {
        case SyntaxKind::OpenParenthesisToken:
        {
            Ptr<SyntaxToken> openParenthesisToken = takeToken();
            Ptr<ExpressionSyntax> expression = parseExpression();
            Ptr<SyntaxToken> closeParenthesisToken = takeToken(SyntaxKind::CloseParenthesisToken);
            return ParenthesizedExpressionSyntax::create(openParenthesisToken, expression, closeParenthesisToken);
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

bool DelphiDirectiveParser::evaluateBool(const Ptr<ExpressionSyntax> expression) const noexcept
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
            Ptr<BinaryExpressionSyntax> binaryExpression = static_cast<BinaryExpressionSyntax*>(expression);
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
        case DefineState::Undefined:
        case DefineState::Unspecified:
        default:
            return false;
    }
}

} // end namespace polyglot::CodeAnalysis
