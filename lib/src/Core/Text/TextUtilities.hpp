#ifndef POLYGLOT_CORE_TEXT_TEXTUTILITIES_H
#define POLYGLOT_CORE_TEXT_TEXTUTILITIES_H

#include "polyglot/Core/Types.hpp"

namespace polyglot::Core::Text
{

class SourceText;

bool isAnyLineBreakCharacter(const char character) noexcept;

pg_size lengthOfLineBreak(const SourceText& sourceText,
                          const pg_size index) noexcept;

pg_size lengthOfLineBreakEndingAt(const SourceText& sourceText,
                                  const pg_size index) noexcept;

} // end namespace polyglot::Core::Text

#endif // POLYGLOT_CORE_TEXT_TEXTUTILITIES_H
