#ifndef POLYGLOT_CODEANALYSIS_CORE_TEXT_TEXTUTILITIES_H
#define POLYGLOT_CODEANALYSIS_CORE_TEXT_TEXTUTILITIES_H

#include "polyglot/Core/Types.hpp"

namespace polyglot::CodeAnalysis
{

class SourceText;

bool isAnyLineBreakCharacter(const char character) noexcept;

pg_size lengthOfLineBreak(const SourceText& sourceText,
                          const pg_size index) noexcept;

pg_size lengthOfLineBreakEndingAt(const SourceText& sourceText,
                                  const pg_size index) noexcept;

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_TEXT_TEXTUTILITIES_H
