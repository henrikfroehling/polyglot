#include "polyglot/CodeAnalysis/Core/DirectiveParser.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
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

namespace polyglot::CodeAnalysis
{

DirectiveParser::DirectiveParser(std::shared_ptr<Lexer> lexer,
                                 const DirectiveStack& context) noexcept
    : Parser{lexer},
      _context{context}
{
    lexer->setMode(LexerMode::Directive);
}

SyntaxNodePtr DirectiveParser::parseDirective(bool isActive,
                                              bool endIsActive,
                                              bool isFirstAfterTokenInFile,
                                              bool isAfterNonWhitespaceOnLine) noexcept
{
    SyntaxTokenPtr openBraceDollar = takeToken(SyntaxKind::OpenBraceDollarToken);
    assert(openBraceDollar != nullptr);

    if (isAfterNonWhitespaceOnLine)
    {
        // TODO error handling
    }

    SyntaxNodePtr result{nullptr};
    SyntaxKind contextualKind = currentToken()->contextualKind();

    switch (contextualKind)
    {
        case SyntaxKind::IfDirectiveKeyword:
            result = parseIfDirective(std::move(openBraceDollar), takeContextualToken(contextualKind), isActive);
            break;
        case SyntaxKind::ElseDirectiveKeyword:
            result = parseElseDirective(std::move(openBraceDollar), takeContextualToken(contextualKind), isActive, endIsActive);
            break;
        case SyntaxKind::ElseIfDirectiveKeyword:
            result = parseElseIfDirective(std::move(openBraceDollar), takeContextualToken(contextualKind), isActive, endIsActive);
            break;
        case SyntaxKind::EndIfDirectiveKeyword:
            result = parseEndIfDirective(std::move(openBraceDollar), takeContextualToken(contextualKind), isActive, endIsActive);
            break;
        case SyntaxKind::DefineDirectiveKeyword:
        case SyntaxKind::UndefDirectiveKeyword:
            result = parseDefineOrUndefDirective(std::move(openBraceDollar), takeContextualToken(contextualKind), isActive, endIsActive);
            break;
        case SyntaxKind::RegionDirectiveKeyword:
            result = parseRegionDirective(std::move(openBraceDollar), takeContextualToken(contextualKind), isActive);
            break;
        case SyntaxKind::EndRegionDirectiveKeyword:
            result = parseEndRegionDirective(std::move(openBraceDollar), takeContextualToken(contextualKind), isActive);
            break;
        default:
            SyntaxTokenPtr identifier = takeToken(SyntaxKind::IdentifierToken);
            SyntaxTokenPtr end = parseEndOfDirective();

            if (!isAfterNonWhitespaceOnLine)
            {
                // TODO error handling
            }

            result = nullptr;
            break;
    }

    return std::move(result);
}

DirectiveTriviaSyntaxPtr DirectiveParser::parseIfDirective(SyntaxTokenPtr openBraceDollarToken,
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

DirectiveTriviaSyntaxPtr DirectiveParser::parseElseDirective(SyntaxTokenPtr openBraceDollarToken,
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

DirectiveTriviaSyntaxPtr DirectiveParser::parseElseIfDirective(SyntaxTokenPtr openBraceDollarToken,
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

DirectiveTriviaSyntaxPtr DirectiveParser::parseEndIfDirective(SyntaxTokenPtr openBraceDollarToken,
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

DirectiveTriviaSyntaxPtr DirectiveParser::parseDefineOrUndefDirective(SyntaxTokenPtr openBraceDollarToken,
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
    {
        return DefineDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword), std::move(name), std::move(endOfDirective), isActive);
    }
    else
    {
        return UndefDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword), std::move(name), std::move(endOfDirective), isActive);
    }
}

DirectiveTriviaSyntaxPtr DirectiveParser::parseRegionDirective(SyntaxTokenPtr openBraceDollarToken,
                                                               SyntaxTokenPtr keyword,
                                                               bool isActive) noexcept
{
    SyntaxTokenPtr endOfDirective = parseEndOfDirective();
    return RegionDirectiveTriviaSyntax::Create(std::move(openBraceDollarToken), std::move(keyword), std::move(endOfDirective), isActive);
}

DirectiveTriviaSyntaxPtr DirectiveParser::parseEndRegionDirective(SyntaxTokenPtr openBraceDollarToken,
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

SyntaxTokenPtr DirectiveParser::parseEndOfDirective() noexcept
{
    if (currentToken()->syntaxKind() != SyntaxKind::EndOfDirectiveToken && currentToken()->syntaxKind() != SyntaxKind::EndOfFileToken)
    {
        // TODO

        while (currentToken()->syntaxKind() != SyntaxKind::EndOfDirectiveToken && currentToken()->syntaxKind() != SyntaxKind::EndOfFileToken)
        {
            // TODO
        }
    }

    SyntaxTokenPtr endOfDirective = currentToken()->syntaxKind() == SyntaxKind::EndOfDirectiveToken
        ? takeToken()
        : nullptr; // TODO create token SyntaxKind::EndOfDirectiveToken

    // TODO

    return endOfDirective;
}

ExpressionSyntaxPtr DirectiveParser::parseExpression() noexcept
{
    return parseLogicalOr();
}

ExpressionSyntaxPtr DirectiveParser::parseLogicalOr() noexcept
{
    ExpressionSyntaxPtr left = parseLogicalAnd();

    while (currentToken()->syntaxKind() == SyntaxKind::OrKeyword)
    {
        SyntaxTokenPtr op = takeToken();
        ExpressionSyntaxPtr right = parseLogicalAnd();
        left = nullptr; // TODO create binary expression
    }

    return std::move(left);
}

ExpressionSyntaxPtr DirectiveParser::parseLogicalAnd() noexcept
{
    ExpressionSyntaxPtr left = parseEquality();

    while (currentToken()->syntaxKind() == SyntaxKind::AndKeyword)
    {
        SyntaxTokenPtr op = takeToken();
        ExpressionSyntaxPtr right = parseEquality();
        left = nullptr; // TODO create binary expression
    }
    
    return std::move(left);
}

ExpressionSyntaxPtr DirectiveParser::parseEquality() noexcept
{
    ExpressionSyntaxPtr left = parseLogicalNot();

    while (currentToken()->syntaxKind() == SyntaxKind::EqualToken || currentToken()->syntaxKind() == SyntaxKind::ExclamationMarkToken)
    {
        SyntaxTokenPtr op = takeToken();
        ExpressionSyntaxPtr right = parseEquality();
        left = nullptr; // TODO create binary expression
    }

    return std::move(left);
}

ExpressionSyntaxPtr DirectiveParser::parseLogicalNot() noexcept
{
    if (currentToken()->syntaxKind() == SyntaxKind::ExclamationMarkToken)
    {
        SyntaxTokenPtr op = takeToken();
        return nullptr; // TODO create prefix unary expression
    }

    return parsePrimary();
}

ExpressionSyntaxPtr DirectiveParser::parsePrimary() noexcept
{
    SyntaxKind syntaxKind = currentToken()->syntaxKind();

    switch (syntaxKind)
    {
        case SyntaxKind::OpenParenthesisToken:
        {
            SyntaxTokenPtr open = takeToken();
            ExpressionSyntaxPtr expression = parseExpression();
            SyntaxTokenPtr close = takeToken();
            break; // TODO create parenthesized expression
        }
        case SyntaxKind::IdentifierToken:
        {
            break; // TODO create identifier token
        }
        case SyntaxKind::TrueKeyword:
        case SyntaxKind::FalseKeyword:
            // TODO create literal expression
            break;
        default:
            // TODO create identifier token
            break;
    }

    return nullptr;
}

bool DirectiveParser::evaluateBool(const ExpressionSyntaxPtr& expression) const noexcept
{
    // TODO
    return false;
}

bool DirectiveParser::isDefined(std::string_view id) const noexcept
{
    DefineState state = _context.isDefined(id);

    switch (state)
    {
        case DefineState::Defined:
            return true;
        case DefineState::Undefined:
            return false;
        case DefineState::Unspecified:
        default:
            return false; // TODO
    }
}

} // end namespace polyglot::CodeAnalysis
