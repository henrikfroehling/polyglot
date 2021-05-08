#ifndef POLYGLOT_CORE_PARSER_QUICKSCANSTATE_H
#define POLYGLOT_CORE_PARSER_QUICKSCANSTATE_H

namespace polyglot::Core::Parser
{

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

} // end namespace polyglot::Core::Parser

#endif // POLYGLOT_CORE_PARSER_QUICKSCANSTATE_H
