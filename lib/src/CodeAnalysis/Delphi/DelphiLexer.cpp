#include "polyglot/CodeAnalysis/Delphi/DelphiLexer.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxFacts.hpp"

namespace polyglot::CodeAnalysis
{

constexpr unsigned MAX_KEYWORD_LENGTH{14};

DelphiLexer::DelphiLexer(std::string_view code) noexcept
    : Lexer{std::move(code)},
      _start{}
{}

SyntaxToken DelphiLexer::nextToken() noexcept
{
    _start = _position;
    SyntaxToken token{SyntaxKind::None, _position, ""};

    if (_position >= _code.length())
    {
        token.setSyntaxKind(SyntaxKind::EndOfTileToken);
        return token;
    }

    char currentCharacter = current();

    switch (currentCharacter)
    {
        case '\0':
            advance();
            token.setSyntaxKind(SyntaxKind::EndOfTileToken);
            break;
        case '.':
        {
            advance();
            currentCharacter = current();

            switch (currentCharacter)
            {
                case '.':
                    advance();
                    token.setSyntaxKind(SyntaxKind::DotDotToken);
                    break;
                case ')':
                    advance();
                    token.setSyntaxKind(SyntaxKind::DotCloseParenthesisToken);
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::DotToken);
                    break;
            }

            break;
        }
        case ',':
            advance();
            token.setSyntaxKind(SyntaxKind::CommaToken);
            break;
        case ';':
            advance();
            token.setSyntaxKind(SyntaxKind::SemiColonToken);
            break;
        case ':':
        {
            advance();
            currentCharacter = current();

            switch (currentCharacter)
            {
                case '=':
                    advance();
                    token.setSyntaxKind(SyntaxKind::ColonEqualToken);
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::ColonToken);
                    break;
            }

            break;
        }
        case '=':
            advance();
            token.setSyntaxKind(SyntaxKind::EqualToken);
            break;
        case '^':
        {
            advance();
            currentCharacter = current();

            switch (currentCharacter)
            {
                case '.':
                    advance();
                    token.setSyntaxKind(SyntaxKind::CaretDotToken);
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::CaretToken);
                    break;
            }

            break;
        }
        case '<':
        {
            advance();
            currentCharacter = current();

            switch (currentCharacter)
            {
                case '=':
                    advance();
                    token.setSyntaxKind(SyntaxKind::LessThanEqualToken);
                    break;
                case '>':
                    advance();
                    token.setSyntaxKind(SyntaxKind::LessThanGreaterThanToken);
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::LessThanToken);
                    break;
            }

            break;
        }
        case '>':
        {
            advance();
            currentCharacter = current();

            switch (currentCharacter)
            {
                case '"':
                    advance();
                    token.setSyntaxKind(SyntaxKind::GreaterThanEqualToken);
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::GreaterThanToken);
                    break;
            }

            break;
        }
        case '(':
        {
            advance();
            currentCharacter = current();

            switch (currentCharacter)
            {
                case '*':
                    advance();
                    token.setSyntaxKind(SyntaxKind::OpenParenthesisAsteriskToken);
                    break;
                case '.':
                    advance();
                    token.setSyntaxKind(SyntaxKind::OpenParenthesisDotToken);
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::OpenParenthesisToken);
                    break;
            }

            break;
        }
        case ')':
            advance();
            token.setSyntaxKind(SyntaxKind::CloseParenthesisToken);
            break;
        case '[':
            advance();
            token.setSyntaxKind(SyntaxKind::OpenBracketToken);
            break;
        case ']':
            advance();
            token.setSyntaxKind(SyntaxKind::CloseBracketToken);
            break;
        case '{':
        {
            advance();
            currentCharacter = current();

            switch (currentCharacter)
            {
                case '$':
                    advance();
                    token.setSyntaxKind(SyntaxKind::OpenBraceDollerToken);
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::OpenBraceToken);
                    break;
            }

            break;
        }
        case '}':
            advance();
            token.setSyntaxKind(SyntaxKind::CloseBraceToken);
            break;
        case '@':
        {
            advance();
            currentCharacter = current();

            switch (currentCharacter)
            {
                case '@':
                    advance();
                    token.setSyntaxKind(SyntaxKind::AtAtToken);
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::AtToken);
                    break;
            }

            break;
        }
        case '+':
            advance();
            token.setSyntaxKind(SyntaxKind::PlusToken);
            break;
        case '-':
        {
            advance();
            currentCharacter = current();

            switch (currentCharacter)
            {
                case '-':
                    advance();
                    token.setSyntaxKind(SyntaxKind::MinusMinusToken);
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::MinusToken);
                    break;
            }

            break;
        }
        case '*':
        {
            advance();
            currentCharacter = current();

            switch (currentCharacter)
            {
                case ')':
                    advance();
                    token.setSyntaxKind(SyntaxKind::AsteriskCloseParenthesisToken);
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::AsteriskToken);
                    break;
            }

            break;
        }
        case '/':
        {
            advance();
            currentCharacter = current();

            switch (currentCharacter)
            {
                case '/':
                    advance();
                    token.setSyntaxKind(SyntaxKind::SlashSlashToken);
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::SlashToken);
                    break;
            }

            break;
        }
        case '&':
            advance();
            token.setSyntaxKind(SyntaxKind::AmpersandToken);
            break;
        case '$':
            advance();
            token.setSyntaxKind(SyntaxKind::DollarToken);
            break;
        case '#':
            advance();
            token.setSyntaxKind(SyntaxKind::HashToken);
            break;
        case '\'':
        case '"':
            lexStringLiteral(token);
            break;
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            lexNumberLiteral(token);
            break;
        case ' ': case '\t': case '\n': case '\r': case '\v':
            lexWhiteSpace(token);
            break;
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H':
        case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P':
        case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
        case 'Y': case 'Z':
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h':
        case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p':
        case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x':
        case 'y': case 'z':
        case '_':
            lexIdentifierOrKeyword(token);
            break;
        default:
            advance();
            break;
    }

    const SyntaxKind tokenKind = token.syntaxKind();

    if (tokenKind != SyntaxKind::EndOfTileToken && tokenKind != SyntaxKind::NumberLiteralToken
        && tokenKind != SyntaxKind::StringLiteralToken && tokenKind != SyntaxKind::IdentifierToken
        && !DelphiSyntaxFacts::isKeyword(tokenKind) && tokenKind != SyntaxKind::WhitespaceToken)
    {
        const pg_size currentLength = _position - _start;
        token.setText(_code.substr(_start, currentLength));
    }

    return token;
}

void DelphiLexer::lexStringLiteral(SyntaxToken& token) noexcept
{
    const char quoteCharacter = current();

    if (quoteCharacter == '\'' || quoteCharacter == '"')
    {
        std::string text{quoteCharacter};
        advance();

        while (true)
        {
            char character = current();
            text += character;

            if (character == quoteCharacter)
            {
                advance();
                break;
            }
            else
                advance();
        }

        token.setText(text.c_str());
        token.setSyntaxKind(SyntaxKind::StringLiteralToken);
    }
    else
        token.setSyntaxKind(SyntaxKind::None);
}

void DelphiLexer::lexNumberLiteral(SyntaxToken& token) noexcept
{
    char character = current();

    while (character >= '0' && character <= '9')
    {
        advance();
        character = current();
    }

    const pg_size currentLength = _position - _start;
    token.setText(_code.substr(_start, currentLength));
    token.setSyntaxKind(SyntaxKind::NumberLiteralToken);
}

void DelphiLexer::lexWhiteSpace(SyntaxToken& token) noexcept
{
    while (std::isspace(current()))
        advance();

    const pg_size currentLength = _position - _start;
    token.setText(_code.substr(_start, currentLength));
    token.setSyntaxKind(SyntaxKind::WhitespaceToken);
}

void DelphiLexer::lexIdentifierOrKeyword(SyntaxToken& token) noexcept
{
    char currentCharacter = current();

    while (true)
    {
        bool isAlphaNumeric{false};

        switch (currentCharacter)
        {
            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H':
            case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P':
            case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
            case 'Y': case 'Z':
            case '_':
            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h':
            case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p':
            case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x':
            case 'y': case 'z':
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            {
                advance();
                currentCharacter = current();
                isAlphaNumeric = true;
                break;
            }
            default:
                isAlphaNumeric = false;
                break;
        }

        if (!isAlphaNumeric)
            break;
    }

    const pg_size currentLength = _position - _start;
    const std::string_view text = _code.substr(_start, currentLength);

    if (text.length() > MAX_KEYWORD_LENGTH)
        token.setSyntaxKind(SyntaxKind::IdentifierToken);
    else
    {
        const SyntaxKind syntaxKind = DelphiSyntaxFacts::keywordKind(text);

        if (syntaxKind == SyntaxKind::None)
            token.setSyntaxKind(SyntaxKind::IdentifierToken);
        else
            token.setSyntaxKind(syntaxKind);
    }

    token.setText(text);
}

} // end namespace polyglot::CodeAnalysis
