#include "polyglot/CodeAnalysis/Delphi/DelphiLexer.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxFacts.hpp"
#include <limits>

namespace polyglot::CodeAnalysis
{

constexpr unsigned MAX_KEYWORD_LENGTH{14};
constexpr char INVALID_CHARACTER = std::numeric_limits<char>::max();

DelphiLexer::DelphiLexer(const SourceText& sourceText) noexcept
    : Lexer{sourceText}
{}

SyntaxToken DelphiLexer::nextToken() noexcept
{
    _leadingTriviaCache.clear();
    lexSyntaxTrivia(false, _leadingTriviaCache);
    start();
    SyntaxToken token{};
    scanSyntaxToken(token);
    _trailingTriviaCache.clear();
    lexSyntaxTrivia(true, _trailingTriviaCache);
    return token;
}

void DelphiLexer::scanSyntaxToken(SyntaxToken& token) noexcept
{
    char character = _textWindow.peekCharacter();

    switch (character)
    {
        case '\0':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::EndOfFileToken);
            break;
        case '.':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case '.':
                    _textWindow.advanceCharacter();
                    token.setSyntaxKind(SyntaxKind::DotDotToken);
                    break;
                case ')':
                    _textWindow.advanceCharacter();
                    token.setSyntaxKind(SyntaxKind::DotCloseParenthesisToken);
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::DotToken);
                    break;
            }

            break;
        }
        case ',':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::CommaToken);
            break;
        case ';':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::SemiColonToken);
            break;
        case ':':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case '=':
                    _textWindow.advanceCharacter();
                    token.setSyntaxKind(SyntaxKind::ColonEqualToken);
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::ColonToken);
                    break;
            }

            break;
        }
        case '=':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::EqualToken);
            break;
        case '^':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case '.':
                    _textWindow.advanceCharacter();
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
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case '=':
                    _textWindow.advanceCharacter();
                    token.setSyntaxKind(SyntaxKind::LessThanEqualToken);
                    break;
                case '>':
                    _textWindow.advanceCharacter();
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
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case '"':
                    _textWindow.advanceCharacter();
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
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case '*':
                    _textWindow.advanceCharacter();
                    token.setSyntaxKind(SyntaxKind::OpenParenthesisAsteriskToken);
                    break;
                case '.':
                    _textWindow.advanceCharacter();
                    token.setSyntaxKind(SyntaxKind::OpenParenthesisDotToken);
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::OpenParenthesisToken);
                    break;
            }

            break;
        }
        case ')':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::CloseParenthesisToken);
            break;
        case '[':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::OpenBracketToken);
            break;
        case ']':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::CloseBracketToken);
            break;
        case '{':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case '$':
                    _textWindow.advanceCharacter();
                    token.setSyntaxKind(SyntaxKind::OpenBraceDollerToken);
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::OpenBraceToken);
                    break;
            }

            break;
        }
        case '}':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::CloseBraceToken);
            break;
        case '@':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case '@':
                    _textWindow.advanceCharacter();
                    token.setSyntaxKind(SyntaxKind::AtAtToken);
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::AtToken);
                    break;
            }

            break;
        }
        case '+':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::PlusToken);
            break;
        case '-':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case '-':
                    _textWindow.advanceCharacter();
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
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case ')':
                    _textWindow.advanceCharacter();
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
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case '/':
                    _textWindow.advanceCharacter();
                    token.setSyntaxKind(SyntaxKind::SlashSlashToken);
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::SlashToken);
                    break;
            }

            break;
        }
        case '&':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::AmpersandToken);
            break;
        case '$':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::DollarToken);
            break;
        case '#':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::HashToken);
            break;
        case '\'':
        case '"':
            scanStringLiteral(token);
            break;
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            scanNumericLiteral(token);
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
lettercase:
            scanIdentifierOrKeyword(token);
            break;
        case INVALID_CHARACTER:
            if (!_textWindow.isReallyAtEnd())
                goto defaultcase;

            token.setSyntaxKind(SyntaxKind::EndOfFileToken);
            break;
        default:
defaultcase:
            if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || character == '_')
                goto lettercase;

            _textWindow.advanceCharacter();
            token.setText(_textWindow.text());
            break;
    }
}

void DelphiLexer::scanStringLiteral(SyntaxToken& token) noexcept
{
    const char quoteCharacter = _textWindow.peekCharacter();

    if (quoteCharacter == '\'' || quoteCharacter == '"')
    {
        std::string text{quoteCharacter};
        _textWindow.advanceCharacter();

        while (true)
        {
            char character = _textWindow.peekCharacter();

            if (character == quoteCharacter)
            {
                _textWindow.advanceCharacter();
                break;
            }
            else if (character == '\r' || character == '\n' || (character == INVALID_CHARACTER && _textWindow.isReallyAtEnd()))
            {
                // TODO error handling
                break;
            }
            else
            {
                _textWindow.advanceCharacter();
            }
        }

        token.setText(_textWindow.text());
        token.setSyntaxKind(SyntaxKind::StringLiteralToken);
    }
    else
        token.setSyntaxKind(SyntaxKind::None);
}

void DelphiLexer::scanIdentifierOrKeyword(SyntaxToken& token) noexcept
{
    if (scanIdentifier(token))
    {
        if (token.text().length() > MAX_KEYWORD_LENGTH)
            token.setSyntaxKind(SyntaxKind::IdentifierToken);
        else
        {
            const SyntaxKind syntaxKind = DelphiSyntaxFacts::keywordKind(token.text());

            if (syntaxKind == SyntaxKind::None)
                token.setSyntaxKind(SyntaxKind::IdentifierToken);
            else
                token.setSyntaxKind(syntaxKind);
        }
    }
}

bool DelphiLexer::scanIdentifier(SyntaxToken& token) noexcept
{
    pg_size currentOffset = _textWindow.offset();
    const auto& characterWindow = _textWindow.characterWindow();
    pg_size characterWindowCount = _textWindow.characterWindowCount();
    pg_size startOffset = currentOffset;

    while (true)
    {
        if (currentOffset == characterWindowCount)
            return false;

        switch (characterWindow[currentOffset])
        {
            case '&':
            case '\0':
            case ' ':
            case '\r':
            case '\n':
            case '\t':
            case '!':
            case '%':
            case '(':
            case ')':
            case '*':
            case '+':
            case ',':
            case '-':
            case '.':
            case '/':
            case ':':
            case ';':
            case '<':
            case '=':
            case '>':
            case '?':
            case '[':
            case ']':
            case '^':
            case '{':
            case '|':
            case '}':
            case '~':
            case '"':
            case '\'':
            {
                _textWindow.advanceCharacter(currentOffset - startOffset);
                token.setText(_textWindow.text());
                return true;
            }
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            {
                if (currentOffset == startOffset)
                    return false;
                else
                    goto letter;
            }
            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H':
            case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P':
            case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
            case 'Y': case 'Z':
            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h':
            case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p':
            case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x':
            case 'y': case 'z':
            case '_':
letter:
                currentOffset++;
                continue;
            default:
                return false;
        }
    }
}

void DelphiLexer::scanNumericLiteral(SyntaxToken& token) noexcept
{
    char character = _textWindow.peekCharacter();

    while (character >= '0' && character <= '9')
    {
        _textWindow.advanceCharacter();
        character = _textWindow.peekCharacter();
    }

    token.setText(_textWindow.text());
    token.setSyntaxKind(SyntaxKind::NumberLiteralToken);
}

void DelphiLexer::lexSyntaxTrivia(bool isTrailing, std::vector<SyntaxTrivia>& triviaList) noexcept
{
    bool onlyWhitespaceOnLine = !isTrailing;

    while (true)
    {
        start();
        char character = _textWindow.peekCharacter();

        if (character == ' ')
        {
            SyntaxTrivia trivia = scanWhitespace();
            triviaList.push_back(trivia);
            continue;
        }
        else if (character > 127)
        {
            if (character == ' ' || character == '\t' || character == '\v' || character == '\f')
                character = ' ';
            else if (character == '\r' || character == '\n')
                character = '\n';
        }

        switch (character)
        {
            case ' ':
            case '\t':
            case '\v':
            case '\f':
            {
                SyntaxTrivia trivia = scanWhitespace();
                triviaList.push_back(trivia);
                break;
            }
            case '/':
                character = _textWindow.peekCharacter(1);

                if (character == '/')
                {
                    if (_textWindow.peekCharacter(2) == '/' && _textWindow.peekCharacter(3) != '/')
                    {
                        if (isTrailing)
                            return;

                        // TODO lex documentation comment
                        break;
                    }

                    scanToEndOfLine();
                    triviaList.emplace_back(SyntaxKind::SingleLineCommentTrivia, _textWindow.text());
                    onlyWhitespaceOnLine = false;
                    break;
                }

                return;
            case '{':
                character = _textWindow.peekCharacter(1);

                if (character != '$')
                {
                    bool isTerminated{false};
                    scanMultiLineComment(isTerminated);

                    if (!isTerminated)
                    {
                        // TODO error handling
                    }

                    triviaList.emplace_back(SyntaxKind::MultiLineCommentTrivia, _textWindow.text());
                    onlyWhitespaceOnLine = false;
                    break;
                }

                return;
            case '(':
                character = _textWindow.peekCharacter(1);

                if (character == '*')
                {
                    if (_textWindow.peekCharacter(2) == '*')
                    {
                        if (isTrailing)
                            return;

                        // TODO lex documentation comment
                        break;
                    }

                    bool isTerminated{false};
                    scanMultiLineComment(isTerminated);

                    if (!isTerminated)
                    {
                        // TODO error handling
                    }

                    triviaList.emplace_back(SyntaxKind::MultiLineCommentTrivia, _textWindow.text());
                    onlyWhitespaceOnLine = false;
                    break;
                }

                return;
            case '\r':
            case '\n':
            {
                SyntaxTrivia trivia = scanEndOfLine();
                triviaList.push_back(trivia);

                if (isTrailing)
                    return;

                onlyWhitespaceOnLine = true;
                break;
            }
            default:
                return;
        }
    }
}

SyntaxTrivia DelphiLexer::scanWhitespace() noexcept
{
top:
    char character = _textWindow.peekCharacter();

    switch (character)
    {
        case '\t':
        case '\v':
        case '\f':
        case ' ':
space:
            _textWindow.advanceCharacter();
            goto top;
        case '\r':
        case '\n':
            break;
        default:
            if (character > 127 && (character == ' ' || character == '\t' || character == '\v' || character == '\f'))
                goto space;

            break;
    }

    return SyntaxTrivia{SyntaxKind::WhitespaceTrivia, _textWindow.text()};
}

void DelphiLexer::scanToEndOfLine() noexcept
{
    char character = _textWindow.peekCharacter();

    while (!(character == '\r' || character == '\n') && (character != INVALID_CHARACTER || !_textWindow.isReallyAtEnd()))
        _textWindow.advanceCharacter();
}

void DelphiLexer::scanMultiLineComment(bool &isTerminated) noexcept
{
    if (_textWindow.peekCharacter() == '(' && _textWindow.peekCharacter(1) == '*')
    {
        _textWindow.advanceCharacter();
        char character{};

        while (true)
        {
            character = _textWindow.peekCharacter();

            if (character == INVALID_CHARACTER || _textWindow.isReallyAtEnd())
            {
                isTerminated = false;
                break;
            }
            else if (character == '*' && _textWindow.peekCharacter(1) == ')')
            {
                _textWindow.advanceCharacter(2);
                isTerminated = true;
                break;
            }
            else
                _textWindow.advanceCharacter();
        }
    }
    else if (_textWindow.peekCharacter() == '{' && _textWindow.peekCharacter(1) != '$')
    {
        _textWindow.advanceCharacter();
        char character{};

        while (true)
        {
            character = _textWindow.peekCharacter();

            if (character == INVALID_CHARACTER || _textWindow.isReallyAtEnd())
            {
                isTerminated = false;
                break;
            }
            else if (_textWindow.peekCharacter(1) == '}')
            {
                _textWindow.advanceCharacter(2);
                isTerminated = true;
                break;
            }
            else
                _textWindow.advanceCharacter();
        }
    }
    else
        isTerminated = false;
}

SyntaxTrivia DelphiLexer::scanEndOfLine() noexcept
{
    char character = _textWindow.peekCharacter();

    switch (character)
    {
        case '\r':
            _textWindow.advanceCharacter();

            if (_textWindow.peekCharacter() == '\n')
            {
                _textWindow.advanceCharacter();
                return SyntaxTrivia{SyntaxKind::EndOfLineTrivia, "\r\n"};
            }

            return SyntaxTrivia{SyntaxKind::EndOfLineTrivia, "\r"};
        case '\n':
            _textWindow.advanceCharacter();
            return SyntaxTrivia{SyntaxKind::EndOfLineTrivia, "\n"};
        default:
            if (character == '\r' || character == '\n')
            {
                _textWindow.advanceCharacter();
                return SyntaxTrivia{SyntaxKind::EndOfLineTrivia, std::string{character}};
            }

        return SyntaxTrivia{SyntaxKind::None, ""};
    }
}

} // end namespace polyglot::CodeAnalysis
