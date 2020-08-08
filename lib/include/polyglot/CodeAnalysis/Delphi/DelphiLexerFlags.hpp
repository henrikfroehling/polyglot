#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXERFLAGS_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXERFLAGS_H

#include <limits>
#include "polyglot/Core/Types.hpp"

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
        QuickScanState::FollowingWhite,                     // White
        QuickScanState::FollowingCR,                     // CR
        QuickScanState::DoneAfterNext,                     // LF
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
        QuickScanState::Done,     // White
        QuickScanState::Done,        // CR
        QuickScanState::Done,      // LF
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
        QuickScanState::Done,     // White
        QuickScanState::Done,               // CR
        QuickScanState::Done,               // LF
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
        QuickScanState::Done,               // CR
        QuickScanState::Done,               // LF
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
        QuickScanState::Done,               // CR
        QuickScanState::Done,               // LF
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
    CharFlags::Complex,                     // (
    CharFlags::Punctuation,                 // )
    CharFlags::Complex,                     // *
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
    CharFlags::Complex,     // `
    CharFlags::Letter,      // a
    CharFlags::Letter,      // b
    CharFlags::Letter,      // c
    CharFlags::Letter,      // d
    CharFlags::Letter,      // e
    CharFlags::Letter,      // f
    CharFlags::Letter,      // g
    CharFlags::Letter,      // h
    CharFlags::Letter,      // i
    CharFlags::Letter,      // j
    CharFlags::Letter,      // k
    CharFlags::Letter,      // k
    CharFlags::Letter,      // m
    CharFlags::Letter,      // n
    CharFlags::Letter,      // o
    CharFlags::Letter,      // p
    CharFlags::Letter,      // q
    CharFlags::Letter,      // r
    CharFlags::Letter,      // s
    CharFlags::Letter,      // t
    CharFlags::Letter,      // u
    CharFlags::Letter,      // v
    CharFlags::Letter,      // w
    CharFlags::Letter,      // x
    CharFlags::Letter,      // y
    CharFlags::Letter,      // z
    CharFlags::Complex,     // {
    CharFlags::Complex,     // |
    CharFlags::Punctuation, // }
    CharFlags::Complex,     // ~
    CharFlags::Complex,     // DEL

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

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXERFLAGS_H
