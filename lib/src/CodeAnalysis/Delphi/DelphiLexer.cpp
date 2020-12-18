#include "polyglot/CodeAnalysis/Delphi/DelphiLexer.hpp"
#include "polyglot/Core/Hashing.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxPool.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"
#include "polyglot/CodeAnalysis/Delphi/DelphiDirectiveParser.hpp"
#include "polyglot/CodeAnalysis/Delphi/DelphiLexerFlags.hpp"
#include "polyglot/CodeAnalysis/Delphi/DelphiLexerStates.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxFacts.hpp"
#include <cassert>
#include <algorithm>

namespace polyglot::CodeAnalysis
{

static constexpr TokenInfo EMPTY_TOKEN_INFO{};
static constexpr unsigned MAX_KEYWORD_LENGTH{14};

DelphiLexer::DelphiLexer(SharedPtr<SourceText> sourceText) noexcept
    : Lexer{std::move(sourceText)},
      _currentTriviaPosition{}
{}

SyntaxToken* DelphiLexer::lex(LexerMode mode) noexcept
{
    switch (_mode)
    {
        case LexerMode::Syntax:
        {
            _leadingTrivia = std::vector<SyntaxNode*>{};
            lexSyntaxTrivia(_textWindow.position() > 0, false, _leadingTrivia);
            TokenInfo tokenInfo = quickScanSyntaxToken();

            if (tokenInfo == EMPTY_TOKEN_INFO)
                tokenInfo = lexSyntaxToken();

            const pg_size tokenPosition = _textWindow.lexemeStartPosition();
            _trailingTrivia = std::vector<SyntaxNode*>{};
            lexSyntaxTrivia(true, true, _trailingTrivia);

            SyntaxToken* syntaxToken = SyntaxPool::createSyntaxToken();
            syntaxToken->setSyntaxKind(tokenInfo.kind);
            syntaxToken->setText(tokenInfo.text);
            syntaxToken->setPosition(tokenPosition);
            syntaxToken->setLeadingTrivia(std::move(_leadingTrivia));
            syntaxToken->setTrailingTrivia(std::move(_trailingTrivia));
            return syntaxToken;
        }
        case LexerMode::Directive:
            return lexDirectiveToken();
    }

    return nullptr;
}

TokenInfo DelphiLexer::quickScanSyntaxToken() noexcept
{
    start();
    QuickScanState previousState = QuickScanState::Initial;
    QuickScanState state = QuickScanState::Initial;
    CharFlags flags = CharFlags::Complex;
    long hashCode = Hashing::FNV_OFFSET_BIAS;
    pg_size offset = _textWindow.offset();
    const std::string_view content = _textWindow.content();

    for (; offset < _textWindow.content().length(); offset++)
    {
        char currentCharacter = content[offset];
        int c = static_cast<int>(currentCharacter);

        const CharFlags previousFlags = flags;
        flags = c < CHAR_PROPERTIES_LENGTH ? CHAR_PROPERTIES[c] : CharFlags::Complex;
        previousState = state;
        state = STATE_TRANSITIONS[static_cast<int>(state)][static_cast<int>(flags)];

        if (state >= QuickScanState::Done)
            goto exitFor;

        hashCode = (hashCode ^ c) * Hashing::FNV_PRIME;
    }

    state = QuickScanState::Bad;

exitFor:
    _textWindow.advanceCharacter(offset - _textWindow.offset());
    assert(state == QuickScanState::Bad || state == QuickScanState::Done);

    if (state == QuickScanState::Done)
    {
        const pg_size lexemeRelativeStart = _textWindow.lexemeRelativeStart();

        TokenInfo tokenInfo = _lexerCache.lookupToken(_textWindow.lexemeText(), hashCode,
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

        return tokenInfo;
    }
    else
    {
        _textWindow.reset(_textWindow.lexemeStartPosition());
        return EMPTY_TOKEN_INFO;
    }
}

TokenInfo DelphiLexer::lexSyntaxToken() noexcept
{
    TokenInfo tokenInfo{};
    start();
    scanSyntaxToken(tokenInfo);
    return tokenInfo;
}

TokenInfo DelphiLexer::lexSyntaxTokenLiteral(std::string_view chars) noexcept
{
    TokenInfo tokenInfo{};
    scanIdentifierOrKeyword(chars, tokenInfo);
    tokenInfo.text = chars;
    return tokenInfo;
}

void DelphiLexer::scanSyntaxToken(TokenInfo& tokenInfo) noexcept
{
    char character = _textWindow.peekCharacter();

    switch (character)
    {
        case '\0':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::EndOfFileToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case '.':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case '.':
                    _textWindow.advanceCharacter();
                    tokenInfo.kind = SyntaxKind::DotDotToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
                case ')':
                    _textWindow.advanceCharacter();
                    tokenInfo.kind = SyntaxKind::DotCloseParenthesisToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
                default:
                    tokenInfo.kind = SyntaxKind::DotToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
            }

            break;
        }
        case ',':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::CommaToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case ';':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::SemiColonToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case ':':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case '=':
                    _textWindow.advanceCharacter();
                    tokenInfo.kind = SyntaxKind::ColonEqualToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
                default:
                    tokenInfo.kind = SyntaxKind::ColonToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
            }

            break;
        }
        case '=':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::EqualToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case '^':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case '.':
                    _textWindow.advanceCharacter();
                    tokenInfo.kind = SyntaxKind::CaretDotToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
                default:
                    tokenInfo.kind = SyntaxKind::CaretToken;
                    tokenInfo.text = _textWindow.lexemeText();
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
                    tokenInfo.kind = SyntaxKind::LessThanEqualToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
                case '>':
                    _textWindow.advanceCharacter();
                    tokenInfo.kind = SyntaxKind::LessThanGreaterThanToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
                default:
                    tokenInfo.kind = SyntaxKind::LessThanToken;
                    tokenInfo.text = _textWindow.lexemeText();
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
                    tokenInfo.kind = SyntaxKind::GreaterThanEqualToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
                default:
                    tokenInfo.kind = SyntaxKind::GreaterThanToken;
                    tokenInfo.text = _textWindow.lexemeText();
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
                    tokenInfo.kind = SyntaxKind::OpenParenthesisDotToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
                default:
                    tokenInfo.kind = SyntaxKind::OpenParenthesisToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
            }

            break;
        }
        case ')':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::CloseParenthesisToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case '[':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::OpenBracketToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case ']':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::CloseBracketToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case '{':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case '$':
                    _textWindow.advanceCharacter();
                    tokenInfo.kind = SyntaxKind::OpenBraceDollarToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
                default:
                    tokenInfo.kind = SyntaxKind::OpenBraceToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
            }

            break;
        }
        case '}':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::CloseBraceToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case '@':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case '@':
                    _textWindow.advanceCharacter();
                    tokenInfo.kind = SyntaxKind::AtAtToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
                default:
                    tokenInfo.kind = SyntaxKind::AtToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
            }

            break;
        }
        case '+':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::PlusToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case '-':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case '-':
                    _textWindow.advanceCharacter();
                    tokenInfo.kind = SyntaxKind::MinusMinusToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
                default:
                    tokenInfo.kind = SyntaxKind::MinusToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
            }

            break;
        }
        case '*':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::AsteriskToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case '/':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case '/':
                    _textWindow.advanceCharacter();
                    tokenInfo.kind = SyntaxKind::SlashSlashToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
                default:
                    tokenInfo.kind = SyntaxKind::SlashToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
            }

            break;
        }
        case '&':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::AmpersandToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case '$':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::DollarToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case '#':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::HashToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case '!':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::ExclamationMarkToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case '\'':
        case '"':
            scanStringLiteral(tokenInfo);
            break;
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            scanNumericLiteral(tokenInfo);
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
            scanIdentifierOrKeyword(tokenInfo);
            break;
        case INVALID_CHARACTER:
            if (!_textWindow.isAtEnd())
                goto defaultcase;

            tokenInfo.kind = SyntaxKind::EndOfFileToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        default:
defaultcase:
            if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || character == '_')
                goto lettercase;

            _textWindow.advanceCharacter();
            tokenInfo.text = _textWindow.lexemeText();
            break;
    }
}

void DelphiLexer::scanStringLiteral(TokenInfo& tokenInfo) noexcept
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
            else if (character == '\r' || character == '\n' || (character == INVALID_CHARACTER && _textWindow.isAtEnd()))
            {
                // TODO error handling
                break;
            }
            else
            {
                _textWindow.advanceCharacter();
            }
        }

        tokenInfo.text = _textWindow.lexemeText();

        if (quoteCharacter == '\'')
            tokenInfo.kind = SyntaxKind::SingleQuotationStringLiteralToken;
        else
            tokenInfo.kind = SyntaxKind::DoubleQuotationStringLiteralToken;
    }
    else
        tokenInfo.kind = SyntaxKind::None;
}

void DelphiLexer::scanIdentifierOrKeyword(TokenInfo& tokenInfo) noexcept
{
    if (scanIdentifier(tokenInfo))
        scanIdentifierOrKeyword(tokenInfo.text, tokenInfo);
}

void DelphiLexer::scanIdentifierOrKeyword(std::string_view chars,
                                          TokenInfo& tokenInfo) noexcept
{
    if (chars.length() > MAX_KEYWORD_LENGTH)
        tokenInfo.kind = SyntaxKind::IdentifierToken;
    else
    {
        const SyntaxKind syntaxKind = DelphiSyntaxFacts::keywordKind(chars, _mode);

        if (syntaxKind == SyntaxKind::None)
            tokenInfo.kind = SyntaxKind::IdentifierToken;
        else
            tokenInfo.kind = syntaxKind;
    }
}

bool DelphiLexer::scanIdentifier(TokenInfo& tokenInfo) noexcept
{
    pg_size currentOffset = _textWindow.offset();
    const std::string_view content = _textWindow.content();
    pg_size startOffset = currentOffset;

    while (true)
    {
        if (currentOffset == content.size())
            return false;

        switch (content[currentOffset])
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
                tokenInfo.text = _textWindow.lexemeText();
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

void DelphiLexer::scanNumericLiteral(TokenInfo& tokenInfo) noexcept
{
    bool isAfterDot{false};

    while (true)
    {
        const char character = _textWindow.peekCharacter();

        if (character >= '0' && character <= '9')
            _textWindow.advanceCharacter();
        else if (character == '.')
        {
            if (isAfterDot) // TODO error handling
                break;

            isAfterDot = true;
            const char character2 = _textWindow.peekCharacter(1);

            if (character2 >= '0' && character <= '9')
                _textWindow.advanceCharacter();
        }
        else
            break;
    }

    tokenInfo.text = _textWindow.lexemeText();
    tokenInfo.kind = SyntaxKind::NumberLiteralToken;
}

void DelphiLexer::lexSyntaxTrivia(bool afterFirstToken,
                                  bool isTrailing,
                                  std::vector<SyntaxNode*>& triviaList) noexcept
{
    bool onlyWhitespaceOnLine = !isTrailing;

    while (true)
    {
        _currentTriviaPosition = _textWindow.position();
        char character = _textWindow.peekCharacter();

        if (character == ' ')
        {
            triviaList.push_back(scanWhitespace());
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
                triviaList.push_back(scanWhitespace());
                break;
            }
            case '/':
                character = _textWindow.peekCharacter(1);

                if (character == '/')
                {
                    scanToEndOfLine();
                    const std::string_view text = _textWindow.substringUntilCurrentPosition(_currentTriviaPosition);

                    SyntaxTrivia* syntaxTrivia = SyntaxPool::createSyntaxTrivia();
                    syntaxTrivia->setSyntaxKind(SyntaxKind::SingleLineCommentTrivia);
                    syntaxTrivia->setText(text);
                    syntaxTrivia->setPosition(_currentTriviaPosition);
                    triviaList.push_back(syntaxTrivia);

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

                    const std::string_view text = _textWindow.substringUntilCurrentPosition(_currentTriviaPosition);

                    SyntaxTrivia* syntaxTrivia = SyntaxPool::createSyntaxTrivia();
                    syntaxTrivia->setSyntaxKind(SyntaxKind::MultiLineCommentTrivia);
                    syntaxTrivia->setText(text);
                    syntaxTrivia->setPosition(_currentTriviaPosition);
                    triviaList.push_back(syntaxTrivia);

                    onlyWhitespaceOnLine = false;
                }
                else
                {
                    _textWindow.reset(_textWindow.position() - 1);
                    lexSingleDirective(true, true, afterFirstToken, isTrailing || !onlyWhitespaceOnLine, triviaList);
                }

                break;
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

                    const std::string_view text = _textWindow.substringUntilCurrentPosition(_currentTriviaPosition);

                    SyntaxTrivia* syntaxTrivia = SyntaxPool::createSyntaxTrivia();
                    syntaxTrivia->setSyntaxKind(SyntaxKind::MultiLineCommentTrivia);
                    syntaxTrivia->setText(text);
                    syntaxTrivia->setPosition(_currentTriviaPosition);
                    triviaList.push_back(syntaxTrivia);

                    onlyWhitespaceOnLine = false;
                    break;
                }
                else
                    _textWindow.reset(_textWindow.position() - 1);

                return;
            case '\r':
            case '\n':
            {
                triviaList.push_back(scanEndOfLine());

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

SyntaxTrivia* DelphiLexer::scanWhitespace() noexcept
{
    long hashCode = Hashing::FNV_OFFSET_BIAS;
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

    const pg_size width = _textWindow.position() - _currentTriviaPosition;
    const std::string_view text = _textWindow.content().substr(_currentTriviaPosition, width);

    if (width == 1 && onlySpaces)
    {
        SyntaxTrivia* syntaxTrivia = SyntaxPool::createSyntaxTrivia();
        syntaxTrivia->setSyntaxKind(SyntaxKind::WhitespaceTrivia);
        syntaxTrivia->setText(text);
        syntaxTrivia->setPosition(_currentTriviaPosition);
        return syntaxTrivia;
    }
    else
    {
        if (width < LexerCache::MAX_CACHED_TOKEN_SIZE)
        {
            TokenInfo tokenInfo = _lexerCache.lookupTrivia(text, hashCode,
                [&]()
                {
                    return TokenInfo{SyntaxKind::WhitespaceTrivia, text };
                });

            SyntaxTrivia* syntaxTrivia = SyntaxPool::createSyntaxTrivia();
            syntaxTrivia->setSyntaxKind(tokenInfo.kind);
            syntaxTrivia->setText(text);
            syntaxTrivia->setPosition(_currentTriviaPosition);
            return syntaxTrivia;
        }
        else
        {
            SyntaxTrivia* syntaxTrivia = SyntaxPool::createSyntaxTrivia();
            syntaxTrivia->setSyntaxKind(SyntaxKind::WhitespaceTrivia);
            syntaxTrivia->setText(text);
            syntaxTrivia->setPosition(_currentTriviaPosition);
            return syntaxTrivia;
        }
    }
}

void DelphiLexer::scanToEndOfLine() noexcept
{
    char character = _textWindow.peekCharacter();

    while (!(character == '\r' || character == '\n') && (character != INVALID_CHARACTER || !_textWindow.isAtEnd()))
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

            if (character == INVALID_CHARACTER || _textWindow.isAtEnd())
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

            if (character == INVALID_CHARACTER || _textWindow.isAtEnd())
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

SyntaxTrivia* DelphiLexer::scanEndOfLine() noexcept
{
    char character = _textWindow.peekCharacter();

    switch (character)
    {
        case '\r':
        {
            _textWindow.advanceCharacter();

            if (_textWindow.peekCharacter() == '\n')
            {
                _textWindow.advanceCharacter();

                SyntaxTrivia* syntaxTrivia = SyntaxPool::createSyntaxTrivia();
                syntaxTrivia->setSyntaxKind(SyntaxKind::EndOfLineTrivia);
                syntaxTrivia->setText("\r\n");
                syntaxTrivia->setPosition(_currentTriviaPosition);
                return syntaxTrivia;
            }

            SyntaxTrivia* syntaxTrivia = SyntaxPool::createSyntaxTrivia();
            syntaxTrivia->setSyntaxKind(SyntaxKind::EndOfLineTrivia);
            syntaxTrivia->setText("\r");
            syntaxTrivia->setPosition(_currentTriviaPosition);
            return syntaxTrivia;
        }
        case '\n':
        {
            _textWindow.advanceCharacter();

            SyntaxTrivia* syntaxTrivia = SyntaxPool::createSyntaxTrivia();
            syntaxTrivia->setSyntaxKind(SyntaxKind::EndOfLineTrivia);
            syntaxTrivia->setText("\n");
            syntaxTrivia->setPosition(_currentTriviaPosition);
            return syntaxTrivia;
        }
        default:
        {
            if (character == '\r' || character == '\n')
            {
                _textWindow.advanceCharacter();

                SyntaxTrivia* syntaxTrivia = SyntaxPool::createSyntaxTrivia();
                syntaxTrivia->setSyntaxKind(SyntaxKind::EndOfLineTrivia);
                syntaxTrivia->setText(std::string{ character });
                syntaxTrivia->setPosition(_currentTriviaPosition);
                return syntaxTrivia;
            }
        }

        {
            SyntaxTrivia* syntaxTrivia = SyntaxPool::createSyntaxTrivia();
            syntaxTrivia->setSyntaxKind(SyntaxKind::None);
            return syntaxTrivia;
        }
    }
}

void DelphiLexer::lexSingleDirective(bool isActive,
                                     bool endIsActive,
                                     bool afterFirstToken,
                                     bool afterNonWhitespaceOnLine,
                                     std::vector<SyntaxNode*>& triviaList) noexcept
{
    char character = _textWindow.peekCharacter();

    if (character == '\t' || character == '\v' || character == '\f' || character == '\r' || character == '\n')
    {
        start();
        triviaList.push_back(scanWhitespace());
    }

    const LexerMode saveMode = _mode;
    DelphiDirectiveParser directiveParser{shared_from_this(), _directives};
    SyntaxNode* directive = directiveParser.parseDirective(isActive, endIsActive, afterFirstToken, afterNonWhitespaceOnLine);
    triviaList.push_back(directive);
    _directives = directive->applyDirectives(_directives);
    setMode(saveMode);
}

SyntaxToken* DelphiLexer::lexDirectiveToken() noexcept
{
    start();
    TokenInfo tokenInfo{};
    scanDirectiveToken(tokenInfo);
    std::vector<SyntaxNode*> trailingTrivia{};
    lexDirectiveTrailingTrivia(trailingTrivia, tokenInfo.kind == SyntaxKind::EndOfDirectiveToken);

    SyntaxToken* syntaxToken = SyntaxPool::createSyntaxToken();
    syntaxToken->setSyntaxKind(tokenInfo.kind);
    syntaxToken->setText(tokenInfo.text);
    syntaxToken->setPosition(_textWindow.lexemeStartPosition());
    syntaxToken->setTrailingTrivia(std::move(trailingTrivia));
    return syntaxToken;
}

void DelphiLexer::scanDirectiveToken(TokenInfo& tokenInfo) noexcept
{
    char character = _textWindow.peekCharacter();

    switch (character)
    {
        case INVALID_CHARACTER:
            if (!_textWindow.isAtEnd())
                goto defaultCase;

            tokenInfo.kind = SyntaxKind::EndOfDirectiveToken;
            break;
        case '\r':
        case '\n':
newLine:
            tokenInfo.kind = SyntaxKind::EndOfDirectiveToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case ')':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::CloseParenthesisToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case '!':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::ExclamationMarkToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case '=':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::EqualToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case '+':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::PlusToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case '-':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::MinusToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case ',':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::CommaToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case '{':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case '$':
                    _textWindow.advanceCharacter();
                    tokenInfo.kind = SyntaxKind::OpenBraceDollarToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
                default:
                    tokenInfo.kind = SyntaxKind::OpenBraceToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
            }

            break;
        }
        case '}':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::EndOfDirectiveToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case '(':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case '$':
                    _textWindow.advanceCharacter();
                    tokenInfo.kind = SyntaxKind::OpenParenthesisDollarToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
                default:
                    tokenInfo.kind = SyntaxKind::OpenParenthesisToken;
                    tokenInfo.text = _textWindow.lexemeText();
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
                    tokenInfo.kind = SyntaxKind::LessThanEqualToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
                case '>':
                    _textWindow.advanceCharacter();
                    tokenInfo.kind = SyntaxKind::LessThanGreaterThanToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
                default:
                    tokenInfo.kind = SyntaxKind::LessThanToken;
                    tokenInfo.text = _textWindow.lexemeText();
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
                    tokenInfo.kind = SyntaxKind::GreaterThanEqualToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
                default:
                    tokenInfo.kind = SyntaxKind::GreaterThanToken;
                    tokenInfo.text = _textWindow.lexemeText();
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
                    tokenInfo.kind = SyntaxKind::EndOfDirectiveToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
                default:
                    tokenInfo.kind = SyntaxKind::AsteriskToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
            }

            break;
        }
        case '\'':
        case '"':
            scanStringLiteral(tokenInfo);
            break;
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            scanNumericLiteral(tokenInfo);
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
letterCase:
            scanIdentifierOrKeyword(tokenInfo);
            break;
        default:
defaultCase:
            if (character == '\r' || character == '\n')
                goto newLine;

            if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || character == '_')
                goto letterCase;

            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::None;
            tokenInfo.text = _textWindow.lexemeText();
            break;
    }
}

void DelphiLexer::lexDirectiveTrailingTrivia(std::vector<SyntaxNode*>& triviaList,
                                             bool includeEndOfLine) noexcept
{
    while (true)
    {
        const pg_size position = _textWindow.position();
        _currentTriviaPosition = position;
        SyntaxNode* trivia = lexDirectiveTrivia();

        if (trivia == nullptr)
            break;

        if (trivia->syntaxKind() == SyntaxKind::EndOfLineTrivia)
        {
            if (!includeEndOfLine)
                triviaList.push_back(trivia);
            else
            {
                _textWindow.reset(position);
                break;
            }
        }
        else
            triviaList.push_back(trivia);
    }
}

SyntaxNode* DelphiLexer::lexDirectiveTrivia() noexcept
{
    char character = _textWindow.peekCharacter();

    switch (character)
    {
        case ' ':
        case '\t':
        case '\v':
        case '\f':
            return scanDirectiveWhitespace();
        case '\r':
        case '\n':
            return scanEndOfLine();
        case '/':
        {
            character = _textWindow.peekCharacter(1);

            if (character == '/')
            {
                scanToEndOfLine();

                SyntaxTrivia* syntaxTrivia = SyntaxPool::createSyntaxTrivia();
                syntaxTrivia->setSyntaxKind(SyntaxKind::SingleLineCommentTrivia);
                syntaxTrivia->setText(_textWindow.lexemeText());
                syntaxTrivia->setPosition(_currentTriviaPosition);
                return syntaxTrivia;
            }

            break;
        }
    }

    return nullptr;
}

SyntaxTrivia* DelphiLexer::scanDirectiveWhitespace() noexcept
{
    const pg_size startPosition = _textWindow.position();

    while (true)
    {
        char character = _textWindow.peekCharacter();

        switch (character)
        {
            case ' ':
            case '\t':
            case '\v':
            case '\f':
                _textWindow.advanceCharacter();
                break;
            default:
                goto endOfWhitespace;
        }
    }

endOfWhitespace:
    SyntaxTrivia* syntaxTrivia = SyntaxPool::createSyntaxTrivia();
    syntaxTrivia->setSyntaxKind(SyntaxKind::WhitespaceTrivia);
    syntaxTrivia->setText(_textWindow.content().substr(startPosition, _textWindow.position() - startPosition));
    syntaxTrivia->setPosition(startPosition);
    return syntaxTrivia;
}

} // end namespace polyglot::CodeAnalysis
