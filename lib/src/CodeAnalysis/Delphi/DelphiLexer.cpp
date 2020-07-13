#include "polyglot/CodeAnalysis/Delphi/DelphiLexer.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxFacts.hpp"
#include <limits>

namespace polyglot::CodeAnalysis
{

constexpr unsigned MAX_KEYWORD_LENGTH{14};
constexpr char INVALID_CHARACTER = std::numeric_limits<char>::max();

DelphiLexer::DelphiLexer(SourceText* sourceText) noexcept
    : Lexer{sourceText}
{}

std::unique_ptr<SyntaxToken> DelphiLexer::nextToken() noexcept
{
    auto ptrToken = std::make_unique<SyntaxToken>();
    lexSyntaxTrivia(false, *ptrToken);
    start();
    scanSyntaxToken(*ptrToken);
    lexSyntaxTrivia(true, *ptrToken);
    return std::move(ptrToken);
}

void DelphiLexer::scanSyntaxToken(SyntaxToken& token) noexcept
{
    char character = _textWindow.peekCharacter();

    switch (character)
    {
        case '\0':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::EndOfFileToken);
            token.setText(_textWindow.text());
            token.setPosition(_textWindow.position());
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
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
                    break;
                case ')':
                    _textWindow.advanceCharacter();
                    token.setSyntaxKind(SyntaxKind::DotCloseParenthesisToken);
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::DotToken);
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
                    break;
            }

            break;
        }
        case ',':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::CommaToken);
            token.setText(_textWindow.text());
            token.setPosition(_textWindow.position());
            break;
        case ';':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::SemiColonToken);
            token.setText(_textWindow.text());
            token.setPosition(_textWindow.position());
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
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::ColonToken);
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
                    break;
            }

            break;
        }
        case '=':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::EqualToken);
            token.setText(_textWindow.text());
            token.setPosition(_textWindow.position());
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
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::CaretToken);
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
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
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
                    break;
                case '>':
                    _textWindow.advanceCharacter();
                    token.setSyntaxKind(SyntaxKind::LessThanGreaterThanToken);
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::LessThanToken);
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
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
                case '=':
                    _textWindow.advanceCharacter();
                    token.setSyntaxKind(SyntaxKind::GreaterThanEqualToken);
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::GreaterThanToken);
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
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
                case '.':
                    _textWindow.advanceCharacter();
                    token.setSyntaxKind(SyntaxKind::OpenParenthesisDotToken);
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::OpenParenthesisToken);
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
                    break;
            }

            break;
        }
        case ')':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::CloseParenthesisToken);
            token.setText(_textWindow.text());
            token.setPosition(_textWindow.position());
            break;
        case '[':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::OpenBracketToken);
            token.setText(_textWindow.text());
            token.setPosition(_textWindow.position());
            break;
        case ']':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::CloseBracketToken);
            token.setText(_textWindow.text());
            token.setPosition(_textWindow.position());
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
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::OpenBraceToken);
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
                    break;
            }

            break;
        }
        case '}':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::CloseBraceToken);
            token.setText(_textWindow.text());
            token.setPosition(_textWindow.position());
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
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::AtToken);
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
                    break;
            }

            break;
        }
        case '+':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::PlusToken);
            token.setText(_textWindow.text());
            token.setPosition(_textWindow.position());
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
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::MinusToken);
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
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
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::SlashToken);
                    token.setText(_textWindow.text());
                    token.setPosition(_textWindow.position());
                    break;
            }

            break;
        }
        case '&':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::AmpersandToken);
            token.setText(_textWindow.text());
            token.setPosition(_textWindow.position());
            break;
        case '$':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::DollarToken);
            token.setText(_textWindow.text());
            token.setPosition(_textWindow.position());
            break;
        case '#':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::HashToken);
            token.setText(_textWindow.text());
            token.setPosition(_textWindow.position());
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
            token.setText(_textWindow.text());
            token.setPosition(_textWindow.position());
            break;
        default:
defaultcase:
            if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || character == '_')
                goto lettercase;

            _textWindow.advanceCharacter();
            token.setText(_textWindow.text());
            token.setPosition(_textWindow.position());
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

    token.setPosition(_textWindow.position());
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

        token.setPosition(_textWindow.position());
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
                token.setPosition(_textWindow.position());
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
    token.setPosition(_textWindow.position());
}

void DelphiLexer::lexSyntaxTrivia(bool isTrailing, SyntaxToken& token) noexcept
{
    while (true)
    {
        start();
        char character = _textWindow.peekCharacter();

        if (character == ' ')
        {
            if (isTrailing)
                token.addTrailingTrivia(scanWhitespace());
            else
                token.addLeadingTrivia(scanWhitespace());

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
                if (isTrailing)
                    token.addTrailingTrivia(scanWhitespace());
                else
                    token.addLeadingTrivia(scanWhitespace());

                break;
            }
            case '/':
                character = _textWindow.peekCharacter(1);

                if (character == '/')
                {
                    scanToEndOfLine();
                    auto ptrSyntaxTrivia = std::make_unique<SyntaxTrivia>(SyntaxKind::SingleLineCommentTrivia, _textWindow.text());

                    if (isTrailing)
                        token.addTrailingTrivia(std::move(ptrSyntaxTrivia));
                    else
                        token.addLeadingTrivia(std::move(ptrSyntaxTrivia));

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

                    auto ptrSyntaxTrivia = std::make_unique<SyntaxTrivia>(SyntaxKind::MultiLineCommentTrivia, _textWindow.text());

                    if (isTrailing)
                        token.addTrailingTrivia(std::move(ptrSyntaxTrivia));
                    else
                        token.addLeadingTrivia(std::move(ptrSyntaxTrivia));

                    break;
                }
                else
                    _textWindow.reset(_textWindow.position() - 1);

                return;
            case '(':
                character = _textWindow.peekCharacter(1);

                if (character == '*')
                {
                    bool isTerminated{false};
                    scanMultiLineComment(isTerminated);

                    if (!isTerminated)
                    {
                        // TODO error handling
                    }

                    auto ptrSyntaxTrivia = std::make_unique<SyntaxTrivia>(SyntaxKind::MultiLineCommentTrivia, _textWindow.text());

                    if (isTrailing)
                        token.addTrailingTrivia(std::move(ptrSyntaxTrivia));
                    else
                        token.addLeadingTrivia(std::move(ptrSyntaxTrivia));

                    break;
                }
                else
                    _textWindow.reset(_textWindow.position() - 1);

                return;
            case '\r':
            case '\n':
            {
                if (isTrailing)
                    token.addTrailingTrivia(scanEndOfLine());
                else
                    token.addLeadingTrivia(scanEndOfLine());

                if (isTrailing)
                    return;

                break;
            }
            default:
                return;
        }
    }
}

std::unique_ptr<SyntaxTrivia> DelphiLexer::scanWhitespace() noexcept
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

    return std::make_unique<SyntaxTrivia>(SyntaxKind::WhitespaceTrivia, _textWindow.text());
}

void DelphiLexer::scanToEndOfLine() noexcept
{
    char character = _textWindow.peekCharacter();

    while (!(character == '\r' || character == '\n') && (character != INVALID_CHARACTER || !_textWindow.isReallyAtEnd()))
    {
        _textWindow.advanceCharacter();
        character = _textWindow.peekCharacter();
    }
}

void DelphiLexer::scanMultiLineComment(bool &isTerminated) noexcept
{
    const char previousCharacter = _textWindow.peekPreviousCharacter(1);
    const char currentCharacter = _textWindow.peekCharacter();

    if (previousCharacter == '(' && currentCharacter == '*')
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
                _textWindow.advanceCharacter();
                isTerminated = true;
                break;
            }
            else
                _textWindow.advanceCharacter();
        }
    }
    else if (previousCharacter == '{' && currentCharacter != '$')
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
            else if (character == '}')
            {
                _textWindow.advanceCharacter();
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

std::unique_ptr<SyntaxTrivia> DelphiLexer::scanEndOfLine() noexcept
{
    char character = _textWindow.peekCharacter();

    switch (character)
    {
        case '\r':
            _textWindow.advanceCharacter();

            if (_textWindow.peekCharacter() == '\n')
            {
                _textWindow.advanceCharacter();
                return std::make_unique<SyntaxTrivia>(SyntaxKind::EndOfLineTrivia, "\r\n");
            }

            return std::make_unique<SyntaxTrivia>(SyntaxKind::EndOfLineTrivia, "\r");
        case '\n':
            _textWindow.advanceCharacter();
            return std::make_unique<SyntaxTrivia>(SyntaxKind::EndOfLineTrivia, "\n");
        default:
            if (character == '\r' || character == '\n')
            {
                _textWindow.advanceCharacter();
                return std::make_unique<SyntaxTrivia>(SyntaxKind::EndOfLineTrivia, std::string{character});
            }

        return std::make_unique<SyntaxTrivia>(SyntaxKind::None, "");
    }
}

} // end namespace polyglot::CodeAnalysis
