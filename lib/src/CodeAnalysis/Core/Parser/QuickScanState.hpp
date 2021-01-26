#ifndef POLYGLOT_CODEANALYSIS_CORE_PARSER_QUICKSCANSTATE_H
#define POLYGLOT_CODEANALYSIS_CORE_PARSER_QUICKSCANSTATE_H

namespace polyglot::CodeAnalysis
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

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_PARSER_QUICKSCANSTATE_H
