#ifndef POLYGLOT_CODEANALYSIS_DELPHI_PARSER_DELPHILEXERSTATES_H
#define POLYGLOT_CODEANALYSIS_DELPHI_PARSER_DELPHILEXERSTATES_H

#include "CodeAnalysis/Core/Parser/QuickScanState.hpp"

namespace polyglot::CodeAnalysis
{

static constexpr QuickScanState STATE_TRANSITIONS[9][11]
{
    // Initial
    {
        QuickScanState::FollowingWhite,             // White
        QuickScanState::FollowingCR,                // CR
        QuickScanState::DoneAfterNext,              // LF
        QuickScanState::Identifier,                 // Letter
        QuickScanState::Number,                     // Digit
        QuickScanState::Punctuation,                // Punctuation
        QuickScanState::Dot,                        // Dot
        QuickScanState::CompoundPunctuationStart,   // Compound Punctuation
        QuickScanState::Bad,                        // Slash
        QuickScanState::Bad,                        // Complex
        QuickScanState::Bad                         // EndOfFile
    },

    // Following White
    {
        QuickScanState::FollowingWhite, // White
        QuickScanState::FollowingCR,    // CR
        QuickScanState::DoneAfterNext,  // LF
        QuickScanState::Done,           // Letter
        QuickScanState::Done,           // Digit
        QuickScanState::Done,           // Punctuation
        QuickScanState::Done,           // Dot
        QuickScanState::Done,           // Compound Punctuation
        QuickScanState::Bad,            // Slash
        QuickScanState::Bad,            // Complex
        QuickScanState::Done            // EndOfFile
    },

    // Following CR
    {
        QuickScanState::Done,           // White
        QuickScanState::Done,           // CR
        QuickScanState::DoneAfterNext,  // LF
        QuickScanState::Done,           // Letter
        QuickScanState::Done,           // Digit
        QuickScanState::Done,           // Punctuation
        QuickScanState::Done,           // Dot
        QuickScanState::Done,           // Compound Punctuation
        QuickScanState::Done,           // Slash
        QuickScanState::Done,           // Complex
        QuickScanState::Done            // EndOfFile
    },

    // Identifier
    {
        QuickScanState::Done,       // White
        QuickScanState::Done,       // CR
        QuickScanState::Done,       // LF
        QuickScanState::Identifier, // Letter
        QuickScanState::Identifier, // Digit
        QuickScanState::Done,       // Punctuation
        QuickScanState::Done,       // Dot
        QuickScanState::Done,       // Compound Punctuation
        QuickScanState::Bad,        // Slash
        QuickScanState::Bad,        // Complex
        QuickScanState::Done        // EndOfFile
    },

    // Number
    {
        QuickScanState::FollowingWhite, // White
        QuickScanState::FollowingCR,    // CR
        QuickScanState::DoneAfterNext,  // LF
        QuickScanState::Bad,            // Letter
        QuickScanState::Number,         // Digit
        QuickScanState::Done,           // Punctuation
        QuickScanState::Bad,            // Dot
        QuickScanState::Done,           // Compound Punctuation
        QuickScanState::Bad,            // Slash
        QuickScanState::Bad,            // Complex
        QuickScanState::Done            // EndOfFile
    },

    // Punctuation
    {
        QuickScanState::Done,   // White
        QuickScanState::Done,   // CR
        QuickScanState::Done,   // LF
        QuickScanState::Done,   // Letter
        QuickScanState::Done,   // Digit
        QuickScanState::Done,   // Punctuation
        QuickScanState::Done,   // Dot
        QuickScanState::Done,   // Compound Punctuation
        QuickScanState::Bad,    // Slash
        QuickScanState::Bad,    // Complex
        QuickScanState::Done    // EndOfFile
    },

    // Dot
    {
        QuickScanState::FollowingWhite, // White
        QuickScanState::Done,           // CR
        QuickScanState::Done,           // LF
        QuickScanState::Done,           // Letter
        QuickScanState::Number,         // Digit
        QuickScanState::Done,           // Punctuation
        QuickScanState::Bad,            // Dot
        QuickScanState::Done,           // Compound Punctuation
        QuickScanState::Bad,            // Slash
        QuickScanState::Bad,            // Complex
        QuickScanState::Done            // EndOfFile
    },

    // Compound Punctuation
    {
        QuickScanState::FollowingWhite, // White
        QuickScanState::Done,           // CR
        QuickScanState::Done,           // LF
        QuickScanState::Done,           // Letter
        QuickScanState::Done,           // Digit
        QuickScanState::Bad,            // Punctuation
        QuickScanState::Done,           // Dot
        QuickScanState::Bad,            // Compound Punctuation
        QuickScanState::Bad,            // Slash
        QuickScanState::Bad,            // Complex
        QuickScanState::Done            // EndOfFile
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

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_PARSER_DELPHILEXERSTATES_H
