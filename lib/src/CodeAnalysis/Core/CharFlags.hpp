#ifndef POLYGLOT_CODEANALYSIS_CORE_CHARFLAGS_H
#define POLYGLOT_CODEANALYSIS_CORE_CHARFLAGS_H

namespace polyglot::CodeAnalysis
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

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_CHARFLAGS_H
