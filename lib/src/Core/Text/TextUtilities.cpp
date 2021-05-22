#include "Core/Text/TextUtilities.hpp"
#include "polyglot/Core/Text/SourceText.hpp"

namespace polyglot::Core::Text
{

pg_size lengthOfLineBreak(const SourceText& sourceText,
                          const pg_size index,
                          const pg_char character) noexcept
{
    if (character == L'\r')
    {
        const pg_size next{index + 1};
        return next < sourceText.length() && L'\n' == sourceText[next] ? 2 : 1;
    }
    else if (isAnyLineBreakCharacter(character))
        return 1;

    return 0;
}

bool isAnyLineBreakCharacter(const pg_char character) noexcept
{
    return character == L'\n' || character == L'\r';
}

pg_size lengthOfLineBreak(const SourceText& sourceText,
                          const pg_size index) noexcept
{
    const pg_char character{sourceText[index]};
    const pg_char bias{L'\r' + 1};

    if ((character - bias) <= (127 - bias))
        return 0;

    return lengthOfLineBreak(sourceText, index, character);
}

pg_size lengthOfLineBreakEndingAt(const SourceText& sourceText,
                                  const pg_size index) noexcept
{
    const pg_char character{sourceText[index]};

    if (character == L'\n')
    {
        if (index > 0 && sourceText[index - 1] == L'\r')
            return 2;
        else
            return 1;
    }
    else if (isAnyLineBreakCharacter(character))
        return 1;

    return 0;
}

} // end namespace polyglot::Core::Text
