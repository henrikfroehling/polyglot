#include "Delphi/Parser/DelphiLexer.hpp"
#include <cassert>
#include <algorithm>
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/ISyntaxTrivia.hpp"
#include "Core/Syntax/SyntaxTrivia.hpp"
#include "Core/Hashing.hpp"
#include "Delphi/Parser/DelphiDirectiveParser.hpp"
#include "Delphi/Parser/DelphiLexerFlags.hpp"
#include "Delphi/Parser/DelphiLexerStates.hpp"
#include "Delphi/Syntax/DelphiSyntaxFacts.hpp"

namespace polyglot::Delphi::Parser
{

using namespace Core::Parser;
using namespace Core::Syntax;
using namespace Core::Text;

using Core::Parser::TokenInfo;

static const TokenInfo EMPTY_TOKEN_INFO{};
static constexpr unsigned MAX_KEYWORD_LENGTH{14};

DelphiLexer::DelphiLexer(SharedPtr<SourceText> sourceText) noexcept
    : Lexer{std::move(sourceText)},
      _currentTriviaPosition{},
      _syntaxFactory{syntaxPool()}
{}

ISyntaxToken* DelphiLexer::lexToken() noexcept
{
    switch (_mode)
    {
        case LexerMode::Syntax:
        {
            std::vector<ISyntaxTrivia*> leadingTrivia{};
            lexSyntaxTrivia(_textWindow.position() > 0, false, leadingTrivia);
            TokenInfo tokenInfo = quickScanSyntaxToken();

            if (tokenInfo == EMPTY_TOKEN_INFO)
                tokenInfo = lexSyntaxToken();

            const pg_size tokenPosition = _textWindow.lexemeStartPosition();
            std::vector<ISyntaxTrivia*> trailingTrivia{};
            lexSyntaxTrivia(true, true, trailingTrivia);

            return _syntaxFactory.tokenWithTrivia(tokenInfo, std::move(leadingTrivia), std::move(trailingTrivia), tokenPosition);
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
    const pg_string_view content = _textWindow.content();

    for (; offset < _textWindow.content().length(); offset++)
    {
        const int c = static_cast<int>(content[offset]);

        flags = c < CHAR_PROPERTIES_LENGTH ? CHAR_PROPERTIES[c] : CharFlags::Complex;
        previousState = state;
        state = STATE_TRANSITIONS[static_cast<int>(state)][static_cast<int>(flags)];

        if (state >= QuickScanState::Done)
            goto exitFor;

        hashCode = (hashCode ^ c) * Hashing::FNV_PRIME;
    }

    if (offset == _textWindow.content().length() && state != QuickScanState::Bad)
        state = QuickScanState::Done;
    else
        state = QuickScanState::Bad;

exitFor:
    _textWindow.advanceCharacter(offset - _textWindow.offset());
    assert(state == QuickScanState::Bad || state == QuickScanState::Done);

    if (state == QuickScanState::Done)
    {
        TokenInfo tokenInfo = _lexerCache.lookupToken(_textWindow.lexemeText(), hashCode,
            [&](pg_string_view chars)
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

TokenInfo DelphiLexer::lexSyntaxTokenLiteral(pg_string_view chars) noexcept
{
    TokenInfo tokenInfo{};
    scanIdentifierOrKeyword(chars, tokenInfo);
    tokenInfo.text = chars;
    return tokenInfo;
}

void DelphiLexer::scanSyntaxToken(TokenInfo& tokenInfo) noexcept
{
    pg_char character = _textWindow.peekCharacter();

    switch (character)
    {
        case L'\0':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::EndOfFileToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case L'.':
        {
            const pg_char nextCharacter = _textWindow.peekCharacter(1);

            if (nextCharacter >= L'0' && nextCharacter <= L'9')
                scanNumericLiteral(tokenInfo);
            else
            {
                _textWindow.advanceCharacter();
                character = _textWindow.peekCharacter();

                switch (character)
                {
                    case L'.':
                        _textWindow.advanceCharacter();
                        tokenInfo.kind = SyntaxKind::DotDotToken;
                        tokenInfo.text = _textWindow.lexemeText();
                        break;
                    case L')':
                        _textWindow.advanceCharacter();
                        tokenInfo.kind = SyntaxKind::DotCloseParenthesisToken;
                        tokenInfo.text = _textWindow.lexemeText();
                        break;
                    default:
                        tokenInfo.kind = SyntaxKind::DotToken;
                        tokenInfo.text = _textWindow.lexemeText();
                        break;
                }
            }

            break;
        }
        case L',':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::CommaToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case L';':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::SemiColonToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case L':':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case L'=':
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
        case L'=':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::EqualToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case L'^':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case L'.':
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
        case L'<':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case L'=':
                    _textWindow.advanceCharacter();
                    tokenInfo.kind = SyntaxKind::LessThanEqualToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
                case L'>':
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
        case L'>':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case L'=':
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
        case L'(':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case L'.':
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
        case L')':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::CloseParenthesisToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case L'[':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::OpenBracketToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case L']':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::CloseBracketToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case L'{':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case L'$':
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
        case L'}':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::CloseBraceToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case L'@':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case L'@':
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
        case L'+':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::PlusToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case L'-':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case L'-':
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
        case L'*':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::AsteriskToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case L'/':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case L'/':
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
        case L'&':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::AmpersandToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case L'$':
        {
            const pg_char nextCharacter = _textWindow.peekCharacter(1);

            if (nextCharacter >= L'0' && nextCharacter <= L'9')
                scanNumericLiteral(tokenInfo);
            else
            {
                _textWindow.advanceCharacter();
                tokenInfo.kind = SyntaxKind::DollarToken;
                tokenInfo.text = _textWindow.lexemeText();
            }

            break;
        }
        case L'#':
        {
            const pg_char nextCharacter = _textWindow.peekCharacter(1);

            if (nextCharacter >= L'0' && nextCharacter <= L'9' || nextCharacter == L'$')
                scanNumericLiteral(tokenInfo);
            else
            {
                _textWindow.advanceCharacter();
                tokenInfo.kind = SyntaxKind::HashToken;
                tokenInfo.text = _textWindow.lexemeText();
            }

            break;
        }
        case L'!':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::ExclamationMarkToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case L'\'':
        case L'"':
            scanStringLiteral(tokenInfo);
            break;
        case L'0': case L'1': case L'2': case L'3': case L'4':
        case L'5': case L'6': case L'7': case L'8': case L'9':
            scanNumericLiteral(tokenInfo);
            break;
        case L'A': case L'B': case L'C': case L'D': case L'E': case L'F': case L'G': case L'H':
        case L'I': case L'J': case L'K': case L'L': case L'M': case L'N': case L'O': case L'P':
        case L'Q': case L'R': case L'S': case L'T': case L'U': case L'V': case L'W': case L'X':
        case L'Y': case L'Z':
        case L'a': case L'b': case L'c': case L'd': case L'e': case L'f': case L'g': case L'h':
        case L'i': case L'j': case L'k': case L'l': case L'm': case L'n': case L'o': case L'p':
        case L'q': case L'r': case L's': case L't': case L'u': case L'v': case L'w': case L'x':
        case L'y': case L'z':
        case L'_':
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
            if ((character >= L'a' && character <= L'z') || (character >= L'A' && character <= L'Z') || character == L'_')
                goto lettercase;

            _textWindow.advanceCharacter();
            tokenInfo.text = _textWindow.lexemeText();
            break;
    }
}

void DelphiLexer::scanStringLiteral(TokenInfo& tokenInfo) noexcept
{
    const pg_char quoteCharacter = _textWindow.peekCharacter();

    if (quoteCharacter == L'\'' || quoteCharacter == L'"')
    {
        pg_string text{quoteCharacter};
        _textWindow.advanceCharacter();

        while (true)
        {
            pg_char character = _textWindow.peekCharacter();

            if (character != quoteCharacter)
            {
                switch (character)
                {
                    case L'\r':
                    case L'\n':
                        goto loopBreakout;
                    case INVALID_CHARACTER:
                    {
                        if (_textWindow.isAtEnd())
                        {
                            // TODO error handling
                            goto loopBreakout;
                        }

                        break;
                    }
                    default:
                        _textWindow.advanceCharacter();
                        break;
                }
            }
            else
            {
                _textWindow.advanceCharacter();
                break;
            }
        }

loopBreakout:

        tokenInfo.text = _textWindow.lexemeText();

        if (quoteCharacter == L'\'')
        {
            if ((tokenInfo.text.length() - 2) == 1)
                tokenInfo.kind = SyntaxKind::SingleQuotationSingleCharLiteralToken;
            else
                tokenInfo.kind = SyntaxKind::SingleQuotationStringLiteralToken;
        }
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

void DelphiLexer::scanIdentifierOrKeyword(pg_string_view chars,
                                          TokenInfo& tokenInfo) noexcept
{
    if (chars.length() > MAX_KEYWORD_LENGTH)
        tokenInfo.kind = SyntaxKind::IdentifierToken;
    else
    {
        const SyntaxKind syntaxKind = Syntax::DelphiSyntaxFacts::keywordKind(chars, _mode);

        if (syntaxKind == SyntaxKind::None)
            tokenInfo.kind = SyntaxKind::IdentifierToken;
        else
            tokenInfo.kind = syntaxKind;
    }
}

bool DelphiLexer::scanIdentifier(TokenInfo& tokenInfo) noexcept
{
    pg_size currentOffset = _textWindow.offset();
    const pg_string_view content = _textWindow.content();
    pg_size startOffset = currentOffset;
    bool hasLetters{false};

    while (true)
    {
        if (currentOffset == content.size())
        {
            if (hasLetters)
            {
                _textWindow.advanceCharacter(currentOffset - startOffset);
                tokenInfo.text = _textWindow.lexemeText();
                return true;
            }

            return false;
        }

        switch (content[currentOffset])
        {
            case L'&':
            case L'\0':
            case L' ':
            case L'\r':
            case L'\n':
            case L'\t':
            case L'!':
            case L'%':
            case L'(':
            case L')':
            case L'*':
            case L'+':
            case L',':
            case L'-':
            case L'.':
            case L'/':
            case L':':
            case L';':
            case L'<':
            case L'=':
            case L'>':
            case L'?':
            case L'[':
            case L']':
            case L'^':
            case L'{':
            case L'|':
            case L'}':
            case L'~':
            case L'"':
            case L'\'':
            {
                _textWindow.advanceCharacter(currentOffset - startOffset);
                tokenInfo.text = _textWindow.lexemeText();
                return true;
            }
            case L'0': case L'1': case L'2': case L'3': case L'4':
            case L'5': case L'6': case L'7': case L'8': case L'9':
            {
                if (currentOffset == startOffset)
                    return false;
                else
                    goto letter;
            }
            case L'A': case L'B': case L'C': case L'D': case L'E': case L'F': case L'G': case L'H':
            case L'I': case L'J': case L'K': case L'L': case L'M': case L'N': case L'O': case L'P':
            case L'Q': case L'R': case L'S': case L'T': case L'U': case L'V': case L'W': case L'X':
            case L'Y': case L'Z':
            case L'a': case L'b': case L'c': case L'd': case L'e': case L'f': case L'g': case L'h':
            case L'i': case L'j': case L'k': case L'l': case L'm': case L'n': case L'o': case L'p':
            case L'q': case L'r': case L's': case L't': case L'u': case L'v': case L'w': case L'x':
            case L'y': case L'z':
            case L'_':
letter:
                currentOffset++;
                hasLetters = true;
                continue;
            default:
                return false;
        }
    }
}

void DelphiLexer::scanNumbers(bool isHex) noexcept
{
    bool breakLoop{false};

    while (true)
    {
        pg_char character = _textWindow.peekCharacter();

        if (character >= L'0' && character <= L'9')
            _textWindow.advanceCharacter();
        else if (isHex)
        {
            switch (character)
            {
                case L'A': case L'B': case L'C': case L'D': case L'E': case L'F':
                case L'a': case L'b': case L'c': case L'd': case L'e': case L'f':
                    _textWindow.advanceCharacter();
                    break;
                default:
                    breakLoop = true;
                    break;
            }
        }
        else
            break;

        if (breakLoop)
            break;
    }
}

void DelphiLexer::scanNumericLiteral(TokenInfo& tokenInfo) noexcept
{
    bool isHex{false};
    bool hasDecimal{false};
    bool hasExponent{false};
    bool isControlCharacter{false};

    pg_char character = _textWindow.peekCharacter();

    if (character == L'$')
    {
        _textWindow.advanceCharacter();
        isHex = true;
    }
    else if (character == L'.')
    {
        _textWindow.advanceCharacter();
        hasDecimal = true;
    }
    else if (character == L'#')
    {
        _textWindow.advanceCharacter();
        isControlCharacter = true;
        character = _textWindow.peekCharacter();

        if (character == L'$')
        {
            _textWindow.advanceCharacter();
            isHex = true;
            scanNumbers(true);
        }
        else
            scanNumbers();
    }

    if (isHex && !isControlCharacter)
        scanNumbers(true);
    else if (!isControlCharacter)
    {
        scanNumbers();
        character = _textWindow.peekCharacter();

        if (!hasDecimal && character == L'.')
        {
            const pg_char nextCharacter = _textWindow.peekCharacter(1);

            if (nextCharacter >= L'0' && nextCharacter <= L'9')
            {
                hasDecimal = true;
                _textWindow.advanceCharacter();
                scanNumbers();
            }
        }

        character = _textWindow.peekCharacter();

        if (character == L'E' || character == L'e')
        {
            hasExponent = true;
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            if (character == L'+' || character == L'-')
                _textWindow.advanceCharacter();

            character = _textWindow.peekCharacter();

            if (character < L'0' || character > L'9')
            {
                // missing number after exponential character
                // TODO error handling => invalid decimal
            }
            else
                scanNumbers();
        }
    }

    tokenInfo.text = _textWindow.lexemeText();

    if (isControlCharacter)
        tokenInfo.kind = SyntaxKind::ControlCharacterLiteral;
    else
        tokenInfo.kind = hasDecimal || hasExponent ? SyntaxKind::RealNumberLiteralToken : SyntaxKind::IntegerNumberLiteralToken;
}

void DelphiLexer::lexSyntaxTrivia(bool afterFirstToken,
                                  bool isTrailing,
                                  std::vector<ISyntaxTrivia*>& triviaList) noexcept
{
    bool onlyWhitespaceOnLine = !isTrailing;

    while (true)
    {
        _currentTriviaPosition = _textWindow.position();
        pg_char character = _textWindow.peekCharacter();

        if (character == L' ')
        {
            triviaList.push_back(scanWhitespace());
            continue;
        }
        else if (character > 127)
        {
            if (character == L' ' || character == L'\t' || character == L'\v' || character == L'\f')
                character = L' ';
            else if (character == L'\r' || character == L'\n')
                character = L'\n';
        }

        switch (character)
        {
            case L' ':
            case L'\t':
            case L'\v':
            case L'\f':
            {
                triviaList.push_back(scanWhitespace());
                break;
            }
            case L'/':
                character = _textWindow.peekCharacter(1);

                if (character == L'/')
                {
                    scanToEndOfLine();
                    const pg_string_view text = _textWindow.substringUntilCurrentPosition(_currentTriviaPosition);
                    ISyntaxTrivia* pSyntaxTrivia = _syntaxFactory.singleLineComment(text, _currentTriviaPosition);
                    triviaList.push_back(pSyntaxTrivia);
                    onlyWhitespaceOnLine = false;
                    break;
                }

                return;
            case L'{':
                character = _textWindow.peekCharacter(1);

                if (character != L'$')
                {
                    bool isTerminated{false};
                    scanMultiLineComment(isTerminated);

                    if (!isTerminated)
                    {
                        // TODO error handling
                    }

                    const pg_string_view text = _textWindow.substringUntilCurrentPosition(_currentTriviaPosition);
                    ISyntaxTrivia* pSyntaxTrivia = _syntaxFactory.multiLineComment(text, _currentTriviaPosition);
                    triviaList.push_back(pSyntaxTrivia);
                    onlyWhitespaceOnLine = false;
                }
                else
                    lexSingleDirective(true, true, afterFirstToken, isTrailing || !onlyWhitespaceOnLine, triviaList);

                break;
            case L'(':
                character = _textWindow.peekCharacter(1);

                if (character == L'*')
                {
                    bool isTerminated{false};
                    scanMultiLineComment(isTerminated);

                    if (!isTerminated)
                    {
                        // TODO error handling
                    }

                    const pg_string_view text = _textWindow.substringUntilCurrentPosition(_currentTriviaPosition);
                    ISyntaxTrivia* pSyntaxTrivia = _syntaxFactory.multiLineComment(text, _currentTriviaPosition);
                    triviaList.push_back(pSyntaxTrivia);
                    onlyWhitespaceOnLine = false;
                    break;
                }

                return;
            case L'\r':
            case L'\n':
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

ISyntaxTrivia* DelphiLexer::scanWhitespace() noexcept
{
    bool loopBreak{false};

    while (true)
    {
        pg_char character = _textWindow.peekCharacter();

        switch (character)
        {
            case L'\t':
            case L'\v':
            case L'\f':
            case L' ':
space:
                _textWindow.advanceCharacter();
                break;
            case L'\r':
            case L'\n':
                loopBreak = true;
                break;
            default:
                if (character > 127 && character == ' ')
                    goto space;
                else
                    loopBreak = true;

                break;
        }

        if (loopBreak)
            break;
    }

    const pg_size width = _textWindow.position() - _currentTriviaPosition;
    const pg_string_view text = _textWindow.content().substr(_currentTriviaPosition, width);
    return _syntaxFactory.whiteSpace(text, _currentTriviaPosition);
}

void DelphiLexer::scanToEndOfLine() noexcept
{
    pg_char character = _textWindow.peekCharacter();

    while (!(character == L'\r' || character == L'\n') && (character != INVALID_CHARACTER || !_textWindow.isAtEnd()))
    {
        _textWindow.advanceCharacter();
        character = _textWindow.peekCharacter();
    }
}

void DelphiLexer::scanMultiLineComment(bool &isTerminated) noexcept
{
    const pg_char startCharacter = _textWindow.peekCharacter();
    _textWindow.advanceCharacter();
    pg_char character = _textWindow.peekCharacter();

    if (startCharacter == L'(' && character == L'*')
    {
        _textWindow.advanceCharacter();

        while (true)
        {
            character = _textWindow.peekCharacter();

            if (character == INVALID_CHARACTER || _textWindow.isAtEnd())
            {
                isTerminated = false;
                break;
            }
            else if (character == L'*' && _textWindow.peekCharacter(1) == L')')
            {
                _textWindow.advanceCharacter();
                isTerminated = true;
                break;
            }
            else
                _textWindow.advanceCharacter();
        }
    }
    else if (startCharacter == L'{' && character != L'$')
    {
        _textWindow.advanceCharacter();

        while (true)
        {
            character = _textWindow.peekCharacter();

            if (character == INVALID_CHARACTER || _textWindow.isAtEnd())
            {
                isTerminated = false;
                break;
            }
            else if (character == L'}')
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

ISyntaxTrivia* DelphiLexer::scanEndOfLine() noexcept
{
    pg_char character = _textWindow.peekCharacter();

    switch (character)
    {
        case L'\r':
        {
            _textWindow.advanceCharacter();

            if (_textWindow.peekCharacter() == L'\n')
            {
                _textWindow.advanceCharacter();
                return _syntaxFactory.carriageReturnLineFeed(_currentTriviaPosition);
            }

            return _syntaxFactory.carriageReturn(_currentTriviaPosition);
        }
        case L'\n':
        {
            _textWindow.advanceCharacter();
            return _syntaxFactory.lineFeed(_currentTriviaPosition);
        }
        default:
        {
            if (character == L'\r' || character == L'\n')
            {
                _textWindow.advanceCharacter();
                return _syntaxFactory.endOfLine(pg_string{character}, _currentTriviaPosition);
            }

            return _syntaxFactory.createSyntaxTrivia(SyntaxKind::None, L"");
        }
    }
}

void DelphiLexer::lexSingleDirective(bool isActive,
                                     bool endIsActive,
                                     bool afterFirstToken,
                                     bool afterNonWhitespaceOnLine,
                                     std::vector<ISyntaxTrivia*>& triviaList) noexcept
{
    pg_char character = _textWindow.peekCharacter();

    if (character == L'\t' || character == L'\v' || character == L'\f' || character == L'\r' || character == L'\n')
    {
        start();
        triviaList.push_back(scanWhitespace());
    }

    const LexerMode saveMode = _mode;
    DelphiDirectiveParser directiveParser{shared_from_this(), _directives};
    ISyntaxTrivia* pDirective = directiveParser.parseDirective(isActive, endIsActive, afterFirstToken, afterNonWhitespaceOnLine);
    triviaList.push_back(pDirective);
    _directives = static_cast<SyntaxTrivia*>(pDirective)->applyDirectives(_directives);
    setMode(saveMode);
}

ISyntaxToken* DelphiLexer::lexDirectiveToken() noexcept
{
    start();
    TokenInfo tokenInfo{};
    scanDirectiveToken(tokenInfo);
    std::vector<ISyntaxTrivia*> trailingTrivia{};
    lexDirectiveTrailingTrivia(trailingTrivia, tokenInfo.kind == SyntaxKind::EndOfDirectiveToken);
    return _syntaxFactory.tokenWithTrailingTrivia(tokenInfo, std::move(trailingTrivia), _textWindow.lexemeStartPosition());
}

void DelphiLexer::scanDirectiveToken(TokenInfo& tokenInfo) noexcept
{
    pg_char character = _textWindow.peekCharacter();

    switch (character)
    {
        case INVALID_CHARACTER:
            if (!_textWindow.isAtEnd())
                goto defaultCase;

            tokenInfo.kind = SyntaxKind::EndOfDirectiveToken;
            break;
        case L'\r':
        case L'\n':
newLine:
            tokenInfo.kind = SyntaxKind::EndOfDirectiveToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case L')':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::CloseParenthesisToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case L'!':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::ExclamationMarkToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case L'=':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::EqualToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case L'+':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::PlusToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case L'-':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::MinusToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case L',':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::CommaToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case L'{':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case L'$':
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
        case L'}':
            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::EndOfDirectiveToken;
            tokenInfo.text = _textWindow.lexemeText();
            break;
        case L'(':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case L'$':
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
        case L'<':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case L'=':
                    _textWindow.advanceCharacter();
                    tokenInfo.kind = SyntaxKind::LessThanEqualToken;
                    tokenInfo.text = _textWindow.lexemeText();
                    break;
                case L'>':
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
        case L'>':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case L'=':
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
        case L'*':
        {
            _textWindow.advanceCharacter();
            character = _textWindow.peekCharacter();

            switch (character)
            {
                case L')':
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
        case L'\'':
        case L'"':
            scanStringLiteral(tokenInfo);
            break;
        case L'0': case L'1': case L'2': case L'3': case L'4':
        case L'5': case L'6': case L'7': case L'8': case L'9':
            scanNumericLiteral(tokenInfo);
            break;
        case L'A': case L'B': case L'C': case L'D': case L'E': case L'F': case L'G': case L'H':
        case L'I': case L'J': case L'K': case L'L': case L'M': case L'N': case L'O': case L'P':
        case L'Q': case L'R': case L'S': case L'T': case L'U': case L'V': case L'W': case L'X':
        case L'Y': case L'Z':
        case L'a': case L'b': case L'c': case L'd': case L'e': case L'f': case L'g': case L'h':
        case L'i': case L'j': case L'k': case L'l': case L'm': case L'n': case L'o': case L'p':
        case L'q': case L'r': case L's': case L't': case L'u': case L'v': case L'w': case L'x':
        case L'y': case L'z':
        case L'_':
letterCase:
            scanIdentifierOrKeyword(tokenInfo);
            break;
        default:
defaultCase:
            if (character == L'\r' || character == L'\n')
                goto newLine;

            if ((character >= L'a' && character <= L'z') || (character >= L'A' && character <= L'Z') || character == L'_')
                goto letterCase;

            _textWindow.advanceCharacter();
            tokenInfo.kind = SyntaxKind::None;
            tokenInfo.text = _textWindow.lexemeText();
            break;
    }
}

void DelphiLexer::lexDirectiveTrailingTrivia(std::vector<ISyntaxTrivia*>& triviaList,
                                             bool includeEndOfLine) noexcept
{
    while (true)
    {
        const pg_size position = _textWindow.position();
        _currentTriviaPosition = position;
        ISyntaxTrivia* pTrivia = lexDirectiveTrivia();

        if (pTrivia == nullptr)
            break;

        if (pTrivia->syntaxKind() == SyntaxKind::EndOfLineTrivia)
        {
            if (!includeEndOfLine)
                triviaList.push_back(pTrivia);
            else
            {
                _textWindow.reset(position);
                break;
            }
        }
        else
            triviaList.push_back(pTrivia);
    }
}

ISyntaxTrivia* DelphiLexer::lexDirectiveTrivia() noexcept
{
    pg_char character = _textWindow.peekCharacter();

    switch (character)
    {
        case L' ':
        case L'\t':
        case L'\v':
        case L'\f':
            return scanDirectiveWhitespace();
        case L'\r':
        case L'\n':
            return scanEndOfLine();
        case L'/':
        {
            character = _textWindow.peekCharacter(1);

            if (character == L'/')
            {
                scanToEndOfLine();
                return _syntaxFactory.singleLineComment(_textWindow.lexemeText(), _currentTriviaPosition);
            }

            break;
        }
    }

    return nullptr;
}

ISyntaxTrivia* DelphiLexer::scanDirectiveWhitespace() noexcept
{
    const pg_size startPosition = _textWindow.position();

    while (true)
    {
        pg_char character = _textWindow.peekCharacter();

        switch (character)
        {
            case L' ':
            case L'\t':
            case L'\v':
            case L'\f':
                _textWindow.advanceCharacter();
                break;
            default:
                goto endOfWhitespace;
        }
    }

endOfWhitespace:
    return _syntaxFactory.whiteSpace(_textWindow.content().substr(startPosition, _textWindow.position() - startPosition), startPosition);
}

} // end namespace polyglot::Delphi::Parser
