#ifndef POLYGLOT_CORE_PARSER_CHARFLAGS_H
#define POLYGLOT_CORE_PARSER_CHARFLAGS_H

namespace polyglot::Core::Parser
{

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

} // end namespace polyglot::Core::Parser

#endif // POLYGLOT_CORE_PARSER_CHARFLAGS_H
