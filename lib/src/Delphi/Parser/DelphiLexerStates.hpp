#ifndef POLYGLOT_DELPHI_PARSER_DELPHILEXERSTATES_H
#define POLYGLOT_DELPHI_PARSER_DELPHILEXERSTATES_H

#include "Core/Parser/QuickScanState.hpp"

namespace polyglot::Delphi::Parser
{

static constexpr Core::Parser::QuickScanState STATE_TRANSITIONS[9][11]
{
    // Initial
    {
        Core::Parser::QuickScanState::FollowingWhite,             // White
        Core::Parser::QuickScanState::FollowingCR,                // CR
        Core::Parser::QuickScanState::DoneAfterNext,              // LF
        Core::Parser::QuickScanState::Identifier,                 // Letter
        Core::Parser::QuickScanState::Number,                     // Digit
        Core::Parser::QuickScanState::Punctuation,                // Punctuation
        Core::Parser::QuickScanState::Dot,                        // Dot
        Core::Parser::QuickScanState::CompoundPunctuationStart,   // Compound Punctuation
        Core::Parser::QuickScanState::Bad,                        // Slash
        Core::Parser::QuickScanState::Bad,                        // Complex
        Core::Parser::QuickScanState::Bad                         // EndOfFile
    },

    // Following White
    {
        Core::Parser::QuickScanState::FollowingWhite, // White
        Core::Parser::QuickScanState::FollowingCR,    // CR
        Core::Parser::QuickScanState::DoneAfterNext,  // LF
        Core::Parser::QuickScanState::Done,           // Letter
        Core::Parser::QuickScanState::Done,           // Digit
        Core::Parser::QuickScanState::Done,           // Punctuation
        Core::Parser::QuickScanState::Done,           // Dot
        Core::Parser::QuickScanState::Done,           // Compound Punctuation
        Core::Parser::QuickScanState::Bad,            // Slash
        Core::Parser::QuickScanState::Bad,            // Complex
        Core::Parser::QuickScanState::Done            // EndOfFile
    },

    // Following CR
    {
        Core::Parser::QuickScanState::Done,           // White
        Core::Parser::QuickScanState::Done,           // CR
        Core::Parser::QuickScanState::DoneAfterNext,  // LF
        Core::Parser::QuickScanState::Done,           // Letter
        Core::Parser::QuickScanState::Done,           // Digit
        Core::Parser::QuickScanState::Done,           // Punctuation
        Core::Parser::QuickScanState::Done,           // Dot
        Core::Parser::QuickScanState::Done,           // Compound Punctuation
        Core::Parser::QuickScanState::Done,           // Slash
        Core::Parser::QuickScanState::Done,           // Complex
        Core::Parser::QuickScanState::Done            // EndOfFile
    },

    // Identifier
    {
        Core::Parser::QuickScanState::Done,       // White
        Core::Parser::QuickScanState::Done,       // CR
        Core::Parser::QuickScanState::Done,       // LF
        Core::Parser::QuickScanState::Identifier, // Letter
        Core::Parser::QuickScanState::Identifier, // Digit
        Core::Parser::QuickScanState::Done,       // Punctuation
        Core::Parser::QuickScanState::Done,       // Dot
        Core::Parser::QuickScanState::Done,       // Compound Punctuation
        Core::Parser::QuickScanState::Bad,        // Slash
        Core::Parser::QuickScanState::Bad,        // Complex
        Core::Parser::QuickScanState::Done        // EndOfFile
    },

    // Number
    {
        Core::Parser::QuickScanState::FollowingWhite, // White
        Core::Parser::QuickScanState::FollowingCR,    // CR
        Core::Parser::QuickScanState::DoneAfterNext,  // LF
        Core::Parser::QuickScanState::Bad,            // Letter
        Core::Parser::QuickScanState::Number,         // Digit
        Core::Parser::QuickScanState::Done,           // Punctuation
        Core::Parser::QuickScanState::Bad,            // Dot
        Core::Parser::QuickScanState::Done,           // Compound Punctuation
        Core::Parser::QuickScanState::Bad,            // Slash
        Core::Parser::QuickScanState::Bad,            // Complex
        Core::Parser::QuickScanState::Done            // EndOfFile
    },

    // Punctuation
    {
        Core::Parser::QuickScanState::Done,   // White
        Core::Parser::QuickScanState::Done,   // CR
        Core::Parser::QuickScanState::Done,   // LF
        Core::Parser::QuickScanState::Done,   // Letter
        Core::Parser::QuickScanState::Done,   // Digit
        Core::Parser::QuickScanState::Done,   // Punctuation
        Core::Parser::QuickScanState::Done,   // Dot
        Core::Parser::QuickScanState::Done,   // Compound Punctuation
        Core::Parser::QuickScanState::Bad,    // Slash
        Core::Parser::QuickScanState::Bad,    // Complex
        Core::Parser::QuickScanState::Done    // EndOfFile
    },

    // Dot
    {
        Core::Parser::QuickScanState::FollowingWhite, // White
        Core::Parser::QuickScanState::Done,           // CR
        Core::Parser::QuickScanState::Done,           // LF
        Core::Parser::QuickScanState::Done,           // Letter
        Core::Parser::QuickScanState::Number,         // Digit
        Core::Parser::QuickScanState::Done,           // Punctuation
        Core::Parser::QuickScanState::Bad,            // Dot
        Core::Parser::QuickScanState::Done,           // Compound Punctuation
        Core::Parser::QuickScanState::Bad,            // Slash
        Core::Parser::QuickScanState::Bad,            // Complex
        Core::Parser::QuickScanState::Done            // EndOfFile
    },

    // Compound Punctuation
    {
        Core::Parser::QuickScanState::FollowingWhite, // White
        Core::Parser::QuickScanState::Done,           // CR
        Core::Parser::QuickScanState::Done,           // LF
        Core::Parser::QuickScanState::Done,           // Letter
        Core::Parser::QuickScanState::Done,           // Digit
        Core::Parser::QuickScanState::Bad,            // Punctuation
        Core::Parser::QuickScanState::Done,           // Dot
        Core::Parser::QuickScanState::Bad,            // Compound Punctuation
        Core::Parser::QuickScanState::Bad,            // Slash
        Core::Parser::QuickScanState::Bad,            // Complex
        Core::Parser::QuickScanState::Done            // EndOfFile
    },

    // Done after next
    {
        Core::Parser::QuickScanState::Done,   // White
        Core::Parser::QuickScanState::Done,   // CR
        Core::Parser::QuickScanState::Done,   // LF
        Core::Parser::QuickScanState::Done,   // Letter
        Core::Parser::QuickScanState::Done,   // Digit
        Core::Parser::QuickScanState::Done,   // Punctuation
        Core::Parser::QuickScanState::Done,   // Dot
        Core::Parser::QuickScanState::Done,   // Compound Punctuation
        Core::Parser::QuickScanState::Done,   // Slash
        Core::Parser::QuickScanState::Done,   // Complex
        Core::Parser::QuickScanState::Done    // EndOfFile
    }
};

} // end namespace polyglot::Delphi::Parser

#endif // POLYGLOT_DELPHI_PARSER_DELPHILEXERSTATES_H
