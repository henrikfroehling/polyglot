#include "polyglot/CodeAnalysis/Delphi/DelphiLexer.hpp"
#include "polyglot/Core/Hashing.hpp"
#include "polyglot/CodeAnalysis/Core/LexerCache.hpp"
#include "polyglot/CodeAnalysis/Delphi/DelphiLexerFlags.hpp"
#include "polyglot/CodeAnalysis/Delphi/DelphiLexerStates.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxFacts.hpp"
#include <cassert>
#include <algorithm>

namespace polyglot::CodeAnalysis
{

static constexpr unsigned MAX_KEYWORD_LENGTH{14};

DelphiLexer::DelphiLexer(SourceText* sourceText) noexcept
    : Lexer{sourceText}
{}

std::shared_ptr<SyntaxToken> DelphiLexer::nextToken() noexcept
{
    _leadingTrivia = std::vector<std::shared_ptr<SyntaxTrivia>>{};
    lexSyntaxTrivia(false);

    auto ptrSyntaxToken = quickScanSyntaxToken();

    if (ptrSyntaxToken == nullptr)
        ptrSyntaxToken = lexSyntaxToken();

    _trailingTrivia = std::vector<std::shared_ptr<SyntaxTrivia>>{};
    lexSyntaxTrivia(true);

    ptrSyntaxToken->setLeadingTrivia(std::move(_leadingTrivia));
    ptrSyntaxToken->setTrailingTrivia(std::move(_trailingTrivia));

    return std::move(ptrSyntaxToken);
}

std::shared_ptr<SyntaxToken> DelphiLexer::quickScanSyntaxToken() noexcept
{
    start();
    QuickScanState previousState = QuickScanState::Initial;
    QuickScanState state = QuickScanState::Initial;
    CharFlags flags = CharFlags::Complex;
    int hashCode = Hashing::FNV_OFFSET_BIAS;
    pg_size offset = _textWindow.offset();
    pg_size characterWindowCount = _textWindow.characterWindowCount();
    characterWindowCount = std::min(characterWindowCount, offset + LexerCache::MAX_CACHED_TOKEN_SIZE);
    auto& characterWindow = _textWindow.characterWindow();

    while (offset < characterWindowCount)
    {
        char currentCharacter = characterWindow[offset];
        int c = static_cast<int>(currentCharacter);

        const CharFlags previousFlags = flags;
        flags = c < CHAR_PROPERTIES_LENGTH ? CHAR_PROPERTIES[c] : CharFlags::Complex;
        previousState = state;
        state = STATE_TRANSITIONS[static_cast<int>(state)][static_cast<int>(flags)];

        if (state >= QuickScanState::Done)
            goto exitWhile;

        hashCode = (hashCode ^ c) * Hashing::FNV_PRIME;
        offset++;

        if (offset == characterWindowCount && !_textWindow.isReallyAtEnd())
        {
            _textWindow.resetOffset(offset);

            if (_textWindow.moreCharacters())
            {
                offset = _textWindow.offset();
                characterWindowCount = _textWindow.characterWindowCount();
                characterWindowCount = std::min(characterWindowCount, offset + LexerCache::MAX_CACHED_TOKEN_SIZE);
            }
        }
    }

    state = QuickScanState::Bad;

exitWhile:
    _textWindow.advanceCharacter(offset - _textWindow.offset());
    assert(state == QuickScanState::Bad || state == QuickScanState::Done);

    if (state == QuickScanState::Done)
    {
        const pg_size lexemeRelativeStart = _textWindow.lexemeRelativeStart();

        auto ptrSyntaxToken = _lexerCache.lookupToken(_textWindow.text(), hashCode,
            [&](std::string_view chars)
            {
                if (previousState == QuickScanState::Identifier)
                    return lexSyntaxTokenLiteral(chars);
                else
                {
                    _textWindow.reset(_textWindow.lexemeStartPosition());
                    return lexSyntaxToken();
                }
            });

        return ptrSyntaxToken;
    }
    else
    {
        _textWindow.reset(_textWindow.lexemeStartPosition());
        return nullptr;
    }
}

std::shared_ptr<SyntaxToken> DelphiLexer::lexSyntaxToken() noexcept
{
    auto ptrToken = std::make_shared<SyntaxToken>();
    start();
    scanSyntaxToken(*ptrToken);
    return std::move(ptrToken);
}

std::shared_ptr<SyntaxToken> DelphiLexer::lexSyntaxTokenLiteral(std::string_view chars) noexcept
{
    auto ptrToken = std::make_shared<SyntaxToken>();
    scanIdentifierOrKeyword(chars, *ptrToken);
    ptrToken->setText(chars);
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
                    break;
                case ')':
                    _textWindow.advanceCharacter();
                    token.setSyntaxKind(SyntaxKind::DotCloseParenthesisToken);
                    token.setText(_textWindow.text());
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::DotToken);
                    token.setText(_textWindow.text());
                    break;
            }

            break;
        }
        case ',':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::CommaToken);
            token.setText(_textWindow.text());
            break;
        case ';':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::SemiColonToken);
            token.setText(_textWindow.text());
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
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::ColonToken);
                    token.setText(_textWindow.text());
                    break;
            }

            break;
        }
        case '=':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::EqualToken);
            token.setText(_textWindow.text());
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
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::CaretToken);
                    token.setText(_textWindow.text());
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
                    break;
                case '>':
                    _textWindow.advanceCharacter();
                    token.setSyntaxKind(SyntaxKind::LessThanGreaterThanToken);
                    token.setText(_textWindow.text());
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::LessThanToken);
                    token.setText(_textWindow.text());
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
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::GreaterThanToken);
                    token.setText(_textWindow.text());
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
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::OpenParenthesisToken);
                    token.setText(_textWindow.text());
                    break;
            }

            break;
        }
        case ')':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::CloseParenthesisToken);
            token.setText(_textWindow.text());
            break;
        case '[':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::OpenBracketToken);
            token.setText(_textWindow.text());
            break;
        case ']':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::CloseBracketToken);
            token.setText(_textWindow.text());
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
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::OpenBraceToken);
                    token.setText(_textWindow.text());
                    break;
            }

            break;
        }
        case '}':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::CloseBraceToken);
            token.setText(_textWindow.text());
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
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::AtToken);
                    token.setText(_textWindow.text());
                    break;
            }

            break;
        }
        case '+':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::PlusToken);
            token.setText(_textWindow.text());
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
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::MinusToken);
                    token.setText(_textWindow.text());
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
                    break;
                default:
                    token.setSyntaxKind(SyntaxKind::SlashToken);
                    token.setText(_textWindow.text());
                    break;
            }

            break;
        }
        case '&':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::AmpersandToken);
            token.setText(_textWindow.text());
            break;
        case '$':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::DollarToken);
            token.setText(_textWindow.text());
            break;
        case '#':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::HashToken);
            token.setText(_textWindow.text());
            break;
        case '!':
            _textWindow.advanceCharacter();
            token.setSyntaxKind(SyntaxKind::ExclamationMarkToken);
            token.setText(_textWindow.text());
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
        scanIdentifierOrKeyword(token.text(), token);
}

void DelphiLexer::scanIdentifierOrKeyword(std::string_view chars,
                                          SyntaxToken& token) noexcept
{
    if (chars.length() > MAX_KEYWORD_LENGTH)
        token.setSyntaxKind(SyntaxKind::IdentifierToken);
    else
    {
        const SyntaxKind syntaxKind = DelphiSyntaxFacts::keywordKind(chars);

        if (syntaxKind == SyntaxKind::None)
            token.setSyntaxKind(SyntaxKind::IdentifierToken);
        else
            token.setSyntaxKind(syntaxKind);
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

void DelphiLexer::lexSyntaxTrivia(bool isTrailing,
                                  bool needsStart) noexcept
{
    while (true)
    {
        if (needsStart)
            start();

        char character = _textWindow.peekCharacter();

        if (character == ' ')
        {
            if (isTrailing)
                _trailingTrivia.emplace_back(scanWhitespace());
            else
                _leadingTrivia.emplace_back(scanWhitespace());

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
                    _trailingTrivia.emplace_back(scanWhitespace());
                else
                    _leadingTrivia.emplace_back(scanWhitespace());

                break;
            }
            case '/':
                character = _textWindow.peekCharacter(1);

                if (character == '/')
                {
                    scanToEndOfLine();
                    auto ptrSyntaxTrivia = std::make_shared<SyntaxTrivia>(SyntaxKind::SingleLineCommentTrivia, _textWindow.text());

                    if (isTrailing)
                        _trailingTrivia.emplace_back(std::move(ptrSyntaxTrivia));
                    else
                        _leadingTrivia.emplace_back(std::move(ptrSyntaxTrivia));

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

                    auto ptrSyntaxTrivia = std::make_shared<SyntaxTrivia>(SyntaxKind::MultiLineCommentTrivia, _textWindow.text());

                    if (isTrailing)
                        _trailingTrivia.emplace_back(std::move(ptrSyntaxTrivia));
                    else
                        _leadingTrivia.emplace_back(std::move(ptrSyntaxTrivia));

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

                    auto ptrSyntaxTrivia = std::make_shared<SyntaxTrivia>(SyntaxKind::MultiLineCommentTrivia, _textWindow.text());

                    if (isTrailing)
                        _trailingTrivia.emplace_back(std::move(ptrSyntaxTrivia));
                    else
                        _leadingTrivia.emplace_back(std::move(ptrSyntaxTrivia));

                    break;
                }
                else
                    _textWindow.reset(_textWindow.position() - 1);

                return;
            case '\r':
            case '\n':
            {
                if (isTrailing)
                    _trailingTrivia.emplace_back(scanEndOfLine());
                else
                    _leadingTrivia.emplace_back(scanEndOfLine());

                if (isTrailing)
                    return;

                break;
            }
            default:
                return;
        }
    }
}

std::shared_ptr<SyntaxTrivia> DelphiLexer::scanWhitespace() noexcept
{
    int hashCode = Hashing::FNV_OFFSET_BIAS;
    bool onlySpaces = true;

top:
    char character = _textWindow.peekCharacter();

    switch (character)
    {
        case '\t':
        case '\v':
        case '\f':
nonspaces:
            onlySpaces = false;
            goto space;
        case ' ':
space:
            _textWindow.advanceCharacter();
            hashCode = Hashing::combineFNVHash(hashCode, character);
            goto top;
        case '\r':
        case '\n':
            break;
        default:
            if (character > 127)
            {
                if (character == ' ')
                    goto space;
                else if (character == '\t' || character == '\v' || character == '\f')
                    goto nonspaces;
            }

            break;
    }

    const pg_size width = _textWindow.width();

    if (width == 1 && onlySpaces)
        return std::make_shared<SyntaxTrivia>(SyntaxKind::WhitespaceTrivia, _textWindow.text());
    else
    {
        if (width < LexerCache::MAX_CACHED_TOKEN_SIZE)
        {
            return _lexerCache.lookupTrivia(_textWindow.text(), hashCode,
                [&]()
                {
                    return std::make_shared<SyntaxTrivia>(SyntaxKind::WhitespaceTrivia, _textWindow.text());
                });
        }
        else
            return std::make_shared<SyntaxTrivia>(SyntaxKind::WhitespaceTrivia, _textWindow.text());
    }
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

std::shared_ptr<SyntaxTrivia> DelphiLexer::scanEndOfLine() noexcept
{
    char character = _textWindow.peekCharacter();

    switch (character)
    {
        case '\r':
            _textWindow.advanceCharacter();

            if (_textWindow.peekCharacter() == '\n')
            {
                _textWindow.advanceCharacter();
                return std::make_shared<SyntaxTrivia>(SyntaxKind::EndOfLineTrivia, "\r\n");
            }

            return std::make_shared<SyntaxTrivia>(SyntaxKind::EndOfLineTrivia, "\r");
        case '\n':
            _textWindow.advanceCharacter();
            return std::make_shared<SyntaxTrivia>(SyntaxKind::EndOfLineTrivia, "\n");
        default:
            if (character == '\r' || character == '\n')
            {
                _textWindow.advanceCharacter();
                return std::make_shared<SyntaxTrivia>(SyntaxKind::EndOfLineTrivia, std::string{character});
            }

        return std::make_shared<SyntaxTrivia>(SyntaxKind::None, "");
    }
}

} // end namespace polyglot::CodeAnalysis
