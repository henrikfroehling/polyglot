#include "TextUtilities.hpp"
#include "SourceText.hpp"

namespace polyglot::Core::Text
{

pg_size lengthOfLineBreak(const SourceText& sourceText,
                          const pg_size index,
                          const char character) noexcept
{
    if (character == '\r')
    {
        const pg_size next{index + 1};
        return next < sourceText.length() && '\n' == sourceText[next] ? 2 : 1;
    }
    else if (isAnyLineBreakCharacter(character))
        return 1;

    return 0;
}

bool isAnyLineBreakCharacter(const char character) noexcept
{
    return character == '\n' || character == '\r';
}

pg_size lengthOfLineBreak(const SourceText& sourceText,
                          const pg_size index) noexcept
{
    const char character{sourceText[index]};
    const char bias{'\r' + 1};

    if ((character - bias) <= (127 - bias))
        return 0;

    return lengthOfLineBreak(sourceText, index, character);
}

pg_size lengthOfLineBreakEndingAt(const SourceText& sourceText,
                                  const pg_size index) noexcept
{
    const char character{sourceText[index]};

    if (character == '\n')
    {
        if (index > 0 && sourceText[index - 1] == '\r')
            return 2;
        else
            return 1;
    }
    else if (isAnyLineBreakCharacter(character))
        return 1;

    return 0;
}

} // end namespace polyglot::Core::Text