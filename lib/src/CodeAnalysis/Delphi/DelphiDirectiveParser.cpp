#include "polyglot/CodeAnalysis/Delphi/DelphiDirectiveParser.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include <cassert>

namespace polyglot::CodeAnalysis
{

DelphiDirectiveParser::DelphiDirectiveParser(std::shared_ptr<Lexer> lexer,
                                             const DirectiveStack& context) noexcept
    : Parser{lexer},
      _context{context}
{
    lexer->setMode(LexerMode::Directive);
}

SyntaxNodePtr DelphiDirectiveParser::parseDirective(bool isActive,
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
        case SyntaxKind::IfKeyword:
            result = parseIfDirective(openBraceDollar, takeContextualToken(contextualKind), isActive);
            break;
        case SyntaxKind::ElseKeyword:
            result = parseElseDirective(openBraceDollar, takeContextualToken(contextualKind), isActive, endIsActive);
            break;
        case SyntaxKind::ElseIfKeyword:
            result = parseElseIfDirective(openBraceDollar, takeContextualToken(contextualKind), isActive, endIsActive);
            break;
        case SyntaxKind::EndIfKeyword:
            result = parseEndIfDirective(openBraceDollar, takeContextualToken(contextualKind), isActive, endIsActive);
            break;
        case SyntaxKind::DefineKeyword:
        case SyntaxKind::UndefKeyword:
            result = parseDefineOrUndefDirective(openBraceDollar, takeContextualToken(contextualKind), isActive, endIsActive);
            break;
        case SyntaxKind::RegionKeyword:
            result = parseRegionDirective(openBraceDollar, takeContextualToken(contextualKind), isActive);
            break;
        case SyntaxKind::EndRegionKeyword:
            result = parseEndRegionDirective(openBraceDollar, takeContextualToken(contextualKind), isActive);
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

DirectiveTriviaSyntaxPtr DelphiDirectiveParser::parseIfDirective(SyntaxTokenPtr openBraceDollarToken,
                                                                 SyntaxTokenPtr keyword,
                                                                 bool isActive) noexcept
{
    ExpressionSyntaxPtr expression = parseExpression();
    SyntaxTokenPtr endOfDirective = parseEndOfDirective();
    const bool isTrue = evaluateBool(expression);
    const bool isBranchTaken = isActive && isTrue;
    // TODO evaluate expression
    // TODO determine if branch is taken
    return nullptr; // TODO create if directive trivia
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
        return nullptr; // TODO create else directive trivia
    }
    else if (_context.hasUnfinishedRegion())
    {
        // TODO error handling
    }
    else if (_context.hasUnfinishedIf())
    {
        // TODO error handling
    }
    else
    {
        // TODO error handling
    }

    // TODO
    return nullptr;
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
        return nullptr; // TODO create else if directive trivia
    }
    else
    {
        // TODO error handling
    }

    // TODO
    return nullptr;
}

DirectiveTriviaSyntaxPtr DelphiDirectiveParser::parseEndIfDirective(SyntaxTokenPtr openBraceDollarToken,
                                                                    SyntaxTokenPtr keyword,
                                                                    bool isActive,
                                                                    bool endIsActive) noexcept
{
    SyntaxTokenPtr endOfDirective = parseEndOfDirective();

    if (_context.hasUnfinishedIf())
    {
        return nullptr; // TODO create end if directive trivia
    }
    else if (_context.hasUnfinishedRegion())
    {
        // TODO error handling
    }
    else
    {
        // TODO error handling
    }

    // TODO
    return nullptr;
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

    SyntaxTokenPtr identifier = takeToken(SyntaxKind::IdentifierToken);
    SyntaxTokenPtr endOfDirective = parseEndOfDirective();

    if (keyword->syntaxKind() == SyntaxKind::DefineKeyword)
    {
        // TODO create define directive trivia
    }
    else
    {
        // TODO create undef directive trivia
    }

    return nullptr;
}

DirectiveTriviaSyntaxPtr DelphiDirectiveParser::parseRegionDirective(SyntaxTokenPtr openBraceDollarToken,
                                                                     SyntaxTokenPtr keyword,
                                                                     bool isActive) noexcept
{
    return nullptr; // TODO create region directive trivia
}

DirectiveTriviaSyntaxPtr DelphiDirectiveParser::parseEndRegionDirective(SyntaxTokenPtr openBraceDollarToken,
                                                                        SyntaxTokenPtr keyword,
                                                                        bool isActive) noexcept
{
    SyntaxTokenPtr endOfDirective = parseEndOfDirective();

    if (_context.hasUnfinishedRegion())
    {
        return nullptr; // TODO create end region directive trivia
    }
    else if (_context.hasUnfinishedIf())
    {
        // TODO error handling
    }
    else
    {
        // TODO error handling
    }

    // TODO create region directive trivia
    return nullptr;
}

SyntaxTokenPtr DelphiDirectiveParser::parseEndOfDirective() noexcept
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

ExpressionSyntaxPtr DelphiDirectiveParser::parseExpression() noexcept
{
    return parseLogicalOr();
}

ExpressionSyntaxPtr DelphiDirectiveParser::parseLogicalOr() noexcept
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

ExpressionSyntaxPtr DelphiDirectiveParser::parseLogicalAnd() noexcept
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

ExpressionSyntaxPtr DelphiDirectiveParser::parseEquality() noexcept
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

ExpressionSyntaxPtr DelphiDirectiveParser::parseLogicalNot() noexcept
{
    if (currentToken()->syntaxKind() == SyntaxKind::ExclamationMarkToken)
    {
        SyntaxTokenPtr op = takeToken();
        return nullptr; // TODO create prefix unary expression
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

bool DelphiDirectiveParser::evaluateBool(ExpressionSyntaxPtr expression) const noexcept
{
    // TODO
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
            return false;
        case DefineState::Unspecified:
        default:
            return false; // TODO
    }
}

} // end namespace polyglot::CodeAnalysis
