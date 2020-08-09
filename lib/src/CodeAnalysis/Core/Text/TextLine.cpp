#include "polyglot/CodeAnalysis/Core/Text/TextLine.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SourceText.hpp"
#include "polyglot/CodeAnalysis/Core/Text/TextUtilities.hpp"
#include <cassert>
#include <stdexcept>

namespace polyglot::CodeAnalysis
{

TextLine::TextLine() noexcept
    : _start{},
      _endIncludingLineBreak{},
      _pSourceText{nullptr}
{}

TextLine::TextLine(SourceText* sourceText,
                   const pg_size start,
                   const pg_size endIncludingLineBreak) noexcept
    : _start{start},
      _endIncludingLineBreak{endIncludingLineBreak},
      _pSourceText{sourceText}
{}

pg_size TextLine::lineNumber() const noexcept
{
    return _pSourceText->indexOf(_start);
}

pg_size TextLine::end() const noexcept
{
    return _endIncludingLineBreak - lineBreakLength();
}

TextSpan TextLine::span() const noexcept
{
    return TextSpan::fromBounds(_start, end());
}

TextSpan TextLine::spanIncludingLineBreak() const noexcept
{
    return TextSpan::fromBounds(_start, _endIncludingLineBreak);
}

TextLine TextLine::fromSpan(SourceText* sourceText,
                            TextSpan& textSpan)
{
    assert(sourceText != nullptr);
    assert(textSpan.start() <= sourceText->length());
    assert(textSpan.end() <= sourceText->length());

    if (sourceText->length() > 0)
    {
        if (textSpan.start() > 0 && !isAnyLineBreakCharacter((*sourceText)[textSpan.start() - 1]))
            throw std::out_of_range{"textSpan"};

        bool endIncludingLineBreak{false};

        if (textSpan.end() > textSpan.start())
            endIncludingLineBreak = isAnyLineBreakCharacter((*sourceText)[textSpan.start() - 1]);

        if (!endIncludingLineBreak && textSpan.end() < textSpan.length())
        {
            const pg_size lineBreakLength = lengthOfLineBreak(*sourceText, textSpan.end());

            if (lineBreakLength > 0)
            {
                endIncludingLineBreak = true;
                textSpan = TextSpan{textSpan.start(), textSpan.length() + lineBreakLength};
            }
        }

        if (textSpan.end() < sourceText->length() && !endIncludingLineBreak)
            throw std::out_of_range{"textSpan"};

        return TextLine{sourceText, textSpan.start(), textSpan.end()};
    }

    return TextLine{sourceText, 0, 0};
}

pg_size TextLine::lineBreakLength() const noexcept
{
    if (_pSourceText->length() == 0 || _endIncludingLineBreak == _start)
        return 0;

    return lengthOfLineBreakEndingAt(*_pSourceText, _endIncludingLineBreak - 1);
}

bool operator==(const TextLine& lhs,
                const TextLine& rhs) noexcept
{
    return *lhs._pSourceText == *rhs._pSourceText
        && lhs._start == rhs._start
        && lhs._endIncludingLineBreak == rhs._endIncludingLineBreak;
}

bool operator!=(const TextLine& lhs,
                const TextLine& rhs) noexcept
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os,
                         const TextLine& textLine) noexcept
{
    if (textLine._pSourceText->length() > 0)
        os << textLine._pSourceText->toString(textLine.span());

    return os;
}

} // end namespace polyglot::CodeAnalysis
