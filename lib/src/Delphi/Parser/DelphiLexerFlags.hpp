#ifndef POLYGLOT_DELPHI_PARSER_DELPHILEXERFLAGS_H
#define POLYGLOT_DELPHI_PARSER_DELPHILEXERFLAGS_H

#include "Core/Parser/CharFlags.hpp"

namespace polyglot::Delphi::Parser
{

static constexpr Core::Parser::CharFlags CHAR_PROPERTIES[255]
{
    // 0 .. 31
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::White,   // TAB
    Core::Parser::CharFlags::LF,      // LF
    Core::Parser::CharFlags::White,   // VT
    Core::Parser::CharFlags::White,   // FF
    Core::Parser::CharFlags::CR,      // CR
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,

    // 32 .. 63
    Core::Parser::CharFlags::White,                       // SPC
    Core::Parser::CharFlags::Punctuation,                 // !
    Core::Parser::CharFlags::Complex,                     // "
    Core::Parser::CharFlags::Punctuation,                 // #
    Core::Parser::CharFlags::Punctuation,                 // $
    Core::Parser::CharFlags::Complex,                     // %
    Core::Parser::CharFlags::Punctuation,                 // &
    Core::Parser::CharFlags::Complex,                     // '
    Core::Parser::CharFlags::Complex,                     // (
    Core::Parser::CharFlags::Punctuation,                 // )
    Core::Parser::CharFlags::Complex,                     // *
    Core::Parser::CharFlags::Punctuation,                 // +
    Core::Parser::CharFlags::Punctuation,                 // ,
    Core::Parser::CharFlags::CompoundPunctuationStart,    // -
    Core::Parser::CharFlags::Dot,                         // .
    Core::Parser::CharFlags::Slash,                       // /
    Core::Parser::CharFlags::Digit,                       // 0
    Core::Parser::CharFlags::Digit,                       // 1
    Core::Parser::CharFlags::Digit,                       // 2
    Core::Parser::CharFlags::Digit,                       // 3
    Core::Parser::CharFlags::Digit,                       // 4
    Core::Parser::CharFlags::Digit,                       // 5
    Core::Parser::CharFlags::Digit,                       // 6
    Core::Parser::CharFlags::Digit,                       // 7
    Core::Parser::CharFlags::Digit,                       // 8
    Core::Parser::CharFlags::Digit,                       // 9
    Core::Parser::CharFlags::CompoundPunctuationStart,    // :
    Core::Parser::CharFlags::Punctuation,                 // ;
    Core::Parser::CharFlags::CompoundPunctuationStart,    // <
    Core::Parser::CharFlags::Punctuation,                 // =
    Core::Parser::CharFlags::CompoundPunctuationStart,    // >
    Core::Parser::CharFlags::Complex,                     // ?

    // 64 .. 95
    Core::Parser::CharFlags::CompoundPunctuationStart,    // @
    Core::Parser::CharFlags::Letter,                      // A
    Core::Parser::CharFlags::Letter,                      // B
    Core::Parser::CharFlags::Letter,                      // C
    Core::Parser::CharFlags::Letter,                      // D
    Core::Parser::CharFlags::Letter,                      // E
    Core::Parser::CharFlags::Letter,                      // F
    Core::Parser::CharFlags::Letter,                      // G
    Core::Parser::CharFlags::Letter,                      // H
    Core::Parser::CharFlags::Letter,                      // I
    Core::Parser::CharFlags::Letter,                      // J
    Core::Parser::CharFlags::Letter,                      // K
    Core::Parser::CharFlags::Letter,                      // L
    Core::Parser::CharFlags::Letter,                      // M
    Core::Parser::CharFlags::Letter,                      // N
    Core::Parser::CharFlags::Letter,                      // O
    Core::Parser::CharFlags::Letter,                      // P
    Core::Parser::CharFlags::Letter,                      // Q
    Core::Parser::CharFlags::Letter,                      // R
    Core::Parser::CharFlags::Letter,                      // S
    Core::Parser::CharFlags::Letter,                      // T
    Core::Parser::CharFlags::Letter,                      // U
    Core::Parser::CharFlags::Letter,                      // V
    Core::Parser::CharFlags::Letter,                      // W
    Core::Parser::CharFlags::Letter,                      // X
    Core::Parser::CharFlags::Letter,                      // Y
    Core::Parser::CharFlags::Letter,                      // Z
    Core::Parser::CharFlags::Punctuation,                 // [
    Core::Parser::CharFlags::Complex,                     // Backslash
    Core::Parser::CharFlags::Punctuation,                 // ]
    Core::Parser::CharFlags::CompoundPunctuationStart,    // ^
    Core::Parser::CharFlags::Letter,                      // _

    // 96 .. 127
    Core::Parser::CharFlags::Complex,     // `
    Core::Parser::CharFlags::Letter,      // a
    Core::Parser::CharFlags::Letter,      // b
    Core::Parser::CharFlags::Letter,      // c
    Core::Parser::CharFlags::Letter,      // d
    Core::Parser::CharFlags::Letter,      // e
    Core::Parser::CharFlags::Letter,      // f
    Core::Parser::CharFlags::Letter,      // g
    Core::Parser::CharFlags::Letter,      // h
    Core::Parser::CharFlags::Letter,      // i
    Core::Parser::CharFlags::Letter,      // j
    Core::Parser::CharFlags::Letter,      // k
    Core::Parser::CharFlags::Letter,      // k
    Core::Parser::CharFlags::Letter,      // m
    Core::Parser::CharFlags::Letter,      // n
    Core::Parser::CharFlags::Letter,      // o
    Core::Parser::CharFlags::Letter,      // p
    Core::Parser::CharFlags::Letter,      // q
    Core::Parser::CharFlags::Letter,      // r
    Core::Parser::CharFlags::Letter,      // s
    Core::Parser::CharFlags::Letter,      // t
    Core::Parser::CharFlags::Letter,      // u
    Core::Parser::CharFlags::Letter,      // v
    Core::Parser::CharFlags::Letter,      // w
    Core::Parser::CharFlags::Letter,      // x
    Core::Parser::CharFlags::Letter,      // y
    Core::Parser::CharFlags::Letter,      // z
    Core::Parser::CharFlags::Complex,     // {
    Core::Parser::CharFlags::Complex,     // |
    Core::Parser::CharFlags::Punctuation, // }
    Core::Parser::CharFlags::Complex,     // ~
    Core::Parser::CharFlags::Complex,     // DEL

    // 128 .. 159
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,

    // 160 .. 191
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,

    // 192 ..
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex,
    Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex, Core::Parser::CharFlags::Complex
};

static constexpr auto CHAR_PROPERTIES_LENGTH = static_cast<int>(sizeof(CHAR_PROPERTIES) / sizeof(CHAR_PROPERTIES[0]));

} // end namespace polyglot::Delphi::Parser

#endif // POLYGLOT_DELPHI_PARSER_DELPHILEXERFLAGS_H
