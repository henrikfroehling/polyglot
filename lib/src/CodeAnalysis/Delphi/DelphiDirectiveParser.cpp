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

DelphiDirectiveTriviaSyntaxPtr DelphiDirectiveParser::parseIfDirective(SyntaxTokenPtr openBraceDollarToken,
                                                                       SyntaxTokenPtr keyword,
                                                                       bool isActive) noexcept
{
    DelphiExpressionSyntaxPtr expression = parseExpression();
    SyntaxTokenPtr endOfDirective = parseEndOfDirective();
    // TODO evaluate expression
    // TODO determine if branch is taken
    return nullptr; // TODO create if directive trivia
}

DelphiDirectiveTriviaSyntaxPtr DelphiDirectiveParser::parseElseDirective(SyntaxTokenPtr openBraceDollarToken,
                                                                         SyntaxTokenPtr keyword,
                                                                         bool isActive,
                                                                         bool endIsActive) noexcept
{
    SyntaxTokenPtr endOfDirective = parseEndOfDirective();
    // TODO
    return nullptr;
}

DelphiDirectiveTriviaSyntaxPtr DelphiDirectiveParser::parseElseIfDirective(SyntaxTokenPtr openBraceDollarToken,
                                                                           SyntaxTokenPtr keyword,
                                                                           bool isActive,
                                                                           bool endIsActive) noexcept
{
    DelphiExpressionSyntaxPtr expression = parseExpression();
    SyntaxTokenPtr endOfDirective = parseEndOfDirective();
    // TODO
    return nullptr;
}

DelphiDirectiveTriviaSyntaxPtr DelphiDirectiveParser::parseEndIfDirective(SyntaxTokenPtr openBraceDollarToken,
                                                                          SyntaxTokenPtr keyword,
                                                                          bool isActive,
                                                                          bool endIsActive) noexcept
{
    SyntaxTokenPtr endOfDirective = parseEndOfDirective();
    // TODO
    return nullptr;
}

DelphiDirectiveTriviaSyntaxPtr DelphiDirectiveParser::parseDefineOrUndefDirective(SyntaxTokenPtr openBraceDollarToken,
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

DelphiDirectiveTriviaSyntaxPtr DelphiDirectiveParser::parseRegionDirective(SyntaxTokenPtr openBraceDollarToken,
                                                                           SyntaxTokenPtr keyword,
                                                                           bool isActive) noexcept
{
    return nullptr;
}

DelphiDirectiveTriviaSyntaxPtr DelphiDirectiveParser::parseEndRegionDirective(SyntaxTokenPtr openBraceDollarToken,
                                                                              SyntaxTokenPtr keyword,
                                                                              bool isActive) noexcept
{
    // TODO create region directive trivia
    return nullptr;
}

SyntaxTokenPtr DelphiDirectiveParser::parseEndOfDirective() noexcept
{
    // TODO
    return nullptr;
}

DelphiExpressionSyntaxPtr DelphiDirectiveParser::parseExpression() noexcept
{
    return parseLogicalOr();
}

DelphiExpressionSyntaxPtr DelphiDirectiveParser::parseLogicalOr() noexcept
{
    DelphiExpressionSyntaxPtr left = parseLogicalAnd();

    while (currentToken()->syntaxKind() == SyntaxKind::OrKeyword)
    {
        SyntaxTokenPtr op = takeToken();
        DelphiExpressionSyntaxPtr right = parseLogicalAnd();
        left = nullptr; // TODO create binary expression
    }

    return std::move(left);
}

DelphiExpressionSyntaxPtr DelphiDirectiveParser::parseLogicalAnd() noexcept
{
    DelphiExpressionSyntaxPtr left = parseEquality();

    while (currentToken()->syntaxKind() == SyntaxKind::AndKeyword)
    {
        SyntaxTokenPtr op = takeToken();
        DelphiExpressionSyntaxPtr right = parseEquality();
        left = nullptr; // TODO create binary expression
    }
    
    return std::move(left);
}

DelphiExpressionSyntaxPtr DelphiDirectiveParser::parseEquality() noexcept
{
    DelphiExpressionSyntaxPtr left = parseLogicalNot();

    while (currentToken()->syntaxKind() == SyntaxKind::EqualToken || currentToken()->syntaxKind() == SyntaxKind::ExclamationMarkToken)
    {
        SyntaxTokenPtr op = takeToken();
        DelphiExpressionSyntaxPtr right = parseEquality();
        left = nullptr; // TODO create binary expression
    }

    return std::move(left);
}

DelphiExpressionSyntaxPtr DelphiDirectiveParser::parseLogicalNot() noexcept
{
    if (currentToken()->syntaxKind() == SyntaxKind::ExclamationMarkToken)
    {
        SyntaxTokenPtr op = takeToken();
        return nullptr; // TODO create prefix unary expression
    }

    return parsePrimary();
}

DelphiExpressionSyntaxPtr DelphiDirectiveParser::parsePrimary() noexcept
{
    SyntaxKind syntaxKind = currentToken()->syntaxKind();

    switch (syntaxKind)
    {
        case SyntaxKind::OpenParenthesisToken:
        {
            SyntaxTokenPtr open = takeToken();
            DelphiExpressionSyntaxPtr expression = parseExpression();
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

} // end namespace polyglot::CodeAnalysis
