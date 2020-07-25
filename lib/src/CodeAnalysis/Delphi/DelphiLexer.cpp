#include "polyglot/CodeAnalysis/Delphi/DelphiLexer.hpp"
#include "polyglot/Core/Hashing.hpp"
#include "polyglot/CodeAnalysis/Delphi/Syntax/DelphiSyntaxFacts.hpp"
#include <cassert>
#include <algorithm>
#include <limits>

namespace polyglot::CodeAnalysis
{

constexpr unsigned MAX_KEYWORD_LENGTH{14};
constexpr char INVALID_CHARACTER = std::numeric_limits<char>::max();
constexpr pg_size MAX_CACHED_TOKEN_SIZE = 50;

enum class QuickScanState : char
{
    Initial,
    FollowingWhite,
    FollowingCR,
    Identifier,
    Number,
    Punctuation,
    Dot,
    CompoundPunctuationStart,
    DoneAfterNext,
    Done,
    Bad = Done + 1
};

enum class CharFlags : char
{
    White,
    CR,
    LF,
    Letter,
    Digit,
    Punctuation,
    Dot,
    CompoundPunctuationStart,
    Slash,
    Complex,
    EndOfFile
};

constexpr QuickScanState STATE_TRANSITIONS[9][11]
{
    // Initial
    {
        QuickScanState::Initial,                     // White
        QuickScanState::Initial,                     // CR
        QuickScanState::Initial,                     // LF
        QuickScanState::Identifier,                  // Letter
        QuickScanState::Number,                      // Digit
        QuickScanState::Punctuation,                 // Punctuation
        QuickScanState::Dot,                         // Dot
        QuickScanState::CompoundPunctuationStart,    // Compound Punctuation
        QuickScanState::Bad,                         // Slash
        QuickScanState::Bad,                         // Complex
        QuickScanState::Bad                          // EndOfFile
    },

    // Following White
    {
        QuickScanState::FollowingWhite,     // White
        QuickScanState::FollowingCR,        // CR
        QuickScanState::DoneAfterNext,      // LF
        QuickScanState::Done,               // Letter
        QuickScanState::Done,               // Digit
        QuickScanState::Done,               // Punctuation
        QuickScanState::Done,               // Dot
        QuickScanState::Done,               // Compound Punctuation
        QuickScanState::Bad,                // Slash
        QuickScanState::Bad,                // Complex
        QuickScanState::Done                // EndOfFile
    },

    // Following CR
    {
        QuickScanState::Done,               // White
        QuickScanState::Done,               // CR
        QuickScanState::DoneAfterNext,      // LF
        QuickScanState::Done,               // Letter
        QuickScanState::Done,               // Digit
        QuickScanState::Done,               // Punctuation
        QuickScanState::Done,               // Dot
        QuickScanState::Done,               // Compound Punctuation
        QuickScanState::Done,               // Slash
        QuickScanState::Done,               // Complex
        QuickScanState::Done                // EndOfFile
    },

    // Identifier
    {
        QuickScanState::FollowingWhite,     // White
        QuickScanState::FollowingCR,        // CR
        QuickScanState::DoneAfterNext,      // LF
        QuickScanState::Identifier,         // Letter
        QuickScanState::Identifier,         // Digit
        QuickScanState::Done,               // Punctuation
        QuickScanState::Done,               // Dot
        QuickScanState::Done,               // Compound Punctuation
        QuickScanState::Bad,                // Slash
        QuickScanState::Bad,                // Complex
        QuickScanState::Done                // EndOfFile
    },

    // Number
    {
        QuickScanState::FollowingWhite,     // White
        QuickScanState::FollowingCR,        // CR
        QuickScanState::DoneAfterNext,      // LF
        QuickScanState::Bad,                // Letter
        QuickScanState::Number,             // Digit
        QuickScanState::Done,               // Punctuation
        QuickScanState::Bad,                // Dot
        QuickScanState::Done,               // Compound Punctuation
        QuickScanState::Bad,                // Slash
        QuickScanState::Bad,                // Complex
        QuickScanState::Done                // EndOfFile
    },

    // Punctuation
    {
        QuickScanState::FollowingWhite,     // White
        QuickScanState::FollowingCR,        // CR
        QuickScanState::DoneAfterNext,      // LF
        QuickScanState::Done,               // Letter
        QuickScanState::Done,               // Digit
        QuickScanState::Done,               // Punctuation
        QuickScanState::Done,               // Dot
        QuickScanState::Done,               // Compound Punctuation
        QuickScanState::Bad,                // Slash
        QuickScanState::Bad,                // Complex
        QuickScanState::Done                // EndOfFile
    },

    // Dot
    {
        QuickScanState::FollowingWhite,     // White
        QuickScanState::FollowingCR,        // CR
        QuickScanState::DoneAfterNext,      // LF
        QuickScanState::Done,               // Letter
        QuickScanState::Number,             // Digit
        QuickScanState::Done,               // Punctuation
        QuickScanState::Bad,                // Dot
        QuickScanState::Done,               // Compound Punctuation
        QuickScanState::Bad,                // Slash
        QuickScanState::Bad,                // Complex
        QuickScanState::Done                // EndOfFile
    },

    // Compound Punctuation
    {
        QuickScanState::FollowingWhite,     // White
        QuickScanState::FollowingCR,        // CR
        QuickScanState::DoneAfterNext,      // LF
        QuickScanState::Done,               // Letter
        QuickScanState::Done,               // Digit
        QuickScanState::Bad,                // Punctuation
        QuickScanState::Done,               // Dot
        QuickScanState::Bad,                // Compound Punctuation
        QuickScanState::Bad,                // Slash
        QuickScanState::Bad,                // Complex
        QuickScanState::Done                // EndOfFile
    },

    // Done after next
    {
        QuickScanState::Done,   // White
        QuickScanState::Done,   // CR
        QuickScanState::Done,   // LF
        QuickScanState::Done,   // Letter
        QuickScanState::Done,   // Digit
        QuickScanState::Done,   // Punctuation
        QuickScanState::Done,   // Dot
        QuickScanState::Done,   // Compound Punctuation
        QuickScanState::Done,   // Slash
        QuickScanState::Done,   // Complex
        QuickScanState::Done    // EndOfFile
    }
};

constexpr CharFlags CHAR_PROPERTIES[255]
{
    // 0 .. 31
    CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex,
    CharFlags::White,   // TAB
    CharFlags::LF,      // LF
    CharFlags::White,   // VT
    CharFlags::White,   // FF
    CharFlags::CR,      // CR
    CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex,
    CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex,

    // 32 .. 63
    CharFlags::White,                       // SPC
    CharFlags::Complex,                     // !
    CharFlags::Complex,                     // "
    CharFlags::Punctuation,                 // #
    CharFlags::Punctuation,                 // $
    CharFlags::Complex,                     // %
    CharFlags::Punctuation,                 // &
    CharFlags::Complex,                     // '
    CharFlags::Punctuation,                 // (
    CharFlags::Punctuation,                 // )
    CharFlags::Punctuation,                 // *
    CharFlags::Punctuation,                 // +
    CharFlags::Punctuation,                 // ,
    CharFlags::CompoundPunctuationStart,    // -
    CharFlags::Dot,                         // .
    CharFlags::Slash,                       // /
    CharFlags::Digit,                       // 0
    CharFlags::Digit,                       // 1
    CharFlags::Digit,                       // 2
    CharFlags::Digit,                       // 3
    CharFlags::Digit,                       // 4
    CharFlags::Digit,                       // 5
    CharFlags::Digit,                       // 6
    CharFlags::Digit,                       // 7
    CharFlags::Digit,                       // 8
    CharFlags::Digit,                       // 9
    CharFlags::CompoundPunctuationStart,    // :
    CharFlags::Punctuation,                 // ;
    CharFlags::CompoundPunctuationStart,    // <
    CharFlags::Punctuation,                 // =
    CharFlags::CompoundPunctuationStart,    // >
    CharFlags::Complex,                     // ?

    // 64 .. 95
    CharFlags::CompoundPunctuationStart,    // @
    CharFlags::Letter,                      // A
    CharFlags::Letter,                      // B
    CharFlags::Letter,                      // C
    CharFlags::Letter,                      // D
    CharFlags::Letter,                      // E
    CharFlags::Letter,                      // F
    CharFlags::Letter,                      // G
    CharFlags::Letter,                      // H
    CharFlags::Letter,                      // I
    CharFlags::Letter,                      // J
    CharFlags::Letter,                      // K
    CharFlags::Letter,                      // L
    CharFlags::Letter,                      // M
    CharFlags::Letter,                      // N
    CharFlags::Letter,                      // O
    CharFlags::Letter,                      // P
    CharFlags::Letter,                      // Q
    CharFlags::Letter,                      // R
    CharFlags::Letter,                      // S
    CharFlags::Letter,                      // T
    CharFlags::Letter,                      // U
    CharFlags::Letter,                      // V
    CharFlags::Letter,                      // W
    CharFlags::Letter,                      // X
    CharFlags::Letter,                      // Y
    CharFlags::Letter,                      // Z
    CharFlags::Punctuation,                 // [
    CharFlags::Complex,                     // Backslash
    CharFlags::Punctuation,                 // ]
    CharFlags::CompoundPunctuationStart,    // ^
    CharFlags::Letter,                      // _

    // 96 .. 127
    CharFlags::Complex,                     // `
    CharFlags::Letter,                      // a
    CharFlags::Letter,                      // b
    CharFlags::Letter,                      // c
    CharFlags::Letter,                      // d
    CharFlags::Letter,                      // e
    CharFlags::Letter,                      // f
    CharFlags::Letter,                      // g
    CharFlags::Letter,                      // h
    CharFlags::Letter,                      // i
    CharFlags::Letter,                      // j
    CharFlags::Letter,                      // k
    CharFlags::Letter,                      // k
    CharFlags::Letter,                      // m
    CharFlags::Letter,                      // n
    CharFlags::Letter,                      // o
    CharFlags::Letter,                      // p
    CharFlags::Letter,                      // q
    CharFlags::Letter,                      // r
    CharFlags::Letter,                      // s
    CharFlags::Letter,                      // t
    CharFlags::Letter,                      // u
    CharFlags::Letter,                      // v
    CharFlags::Letter,                      // w
    CharFlags::Letter,                      // x
    CharFlags::Letter,                      // y
    CharFlags::Letter,                      // z
    CharFlags::Punctuation,                 // {
    CharFlags::CompoundPunctuationStart,    // |
    CharFlags::Punctuation,                 // }
    CharFlags::CompoundPunctuationStart,    // ~
    CharFlags::Complex,                     // DEL

    // 128 .. 159
    CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex,
    CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex,
    CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex,
    CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex,

    // 160 .. 191
    CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex,
    CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex,
    CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex,
    CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex,

    // 192 ..
    CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex,
    CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex,
    CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex,
    CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex, CharFlags::Complex
};

constexpr auto CHAR_PROPERTIES_LENGTH = sizeof(CHAR_PROPERTIES) / sizeof(CHAR_PROPERTIES[0]);

DelphiLexer::DelphiLexer(SourceText* sourceText) noexcept
    : Lexer{sourceText}
{}

std::shared_ptr<SyntaxToken> DelphiLexer::nextToken() noexcept
{
    auto ptrSyntaxToken = quickScanSyntaxToken();

    if (ptrSyntaxToken == nullptr)
        return lexSyntaxToken();

    return std::move(ptrSyntaxToken);
}

std::shared_ptr<SyntaxToken> DelphiLexer::quickScanSyntaxToken() noexcept
{
    start();
    QuickScanState state = QuickScanState::Initial;
    pg_size offset = _textWindow.offset();
    pg_size characterWindowCount = _textWindow.characterWindowCount();
    characterWindowCount = std::min(characterWindowCount, offset + MAX_CACHED_TOKEN_SIZE);
    int hashCode = Hashing::FNV_OFFSET_BIAS;
    auto& characterWindow = _textWindow.characterWindow();

    for (; offset < characterWindowCount; offset++)
    {
        char currentCharacter = characterWindow[offset];
        int c = static_cast<int>(currentCharacter);

        CharFlags flags = c < CHAR_PROPERTIES_LENGTH ? CHAR_PROPERTIES[c] : CharFlags::Complex;
        state = STATE_TRANSITIONS[static_cast<int>(state)][static_cast<int>(flags)];

        if (state >= QuickScanState::Done)
            goto exitWhile;

        hashCode = (hashCode ^ c) * Hashing::FNV_PRIME;
    }

    state = QuickScanState::Bad;

exitWhile:
    _textWindow.advanceCharacter(offset - _textWindow.offset());
    assert(state == QuickScanState::Bad || state == QuickScanState::Done);

    if (state == QuickScanState::Done)
    {
        const pg_size lexemeRelativeStart = _textWindow.lexemeRelativeStart();

        auto ptrSyntaxToken = _lexerCache.lookupToken(std::string_view{characterWindow.data() + lexemeRelativeStart, offset - lexemeRelativeStart}, hashCode,
            [&]()
            {
                _textWindow.reset(_textWindow.lexemeStartPosition());
                return lexSyntaxToken();
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
                    auto ptrSyntaxTrivia = std::make_shared<SyntaxTrivia>(SyntaxKind::SingleLineCommentTrivia, _textWindow.text());

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

                    auto ptrSyntaxTrivia = std::make_shared<SyntaxTrivia>(SyntaxKind::MultiLineCommentTrivia, _textWindow.text());

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

                    auto ptrSyntaxTrivia = std::make_shared<SyntaxTrivia>(SyntaxKind::MultiLineCommentTrivia, _textWindow.text());

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

std::shared_ptr<SyntaxTrivia> DelphiLexer::scanWhitespace() noexcept
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

    return std::make_shared<SyntaxTrivia>(SyntaxKind::WhitespaceTrivia, _textWindow.text());
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
