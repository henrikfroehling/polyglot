#include "CodeAnalysis/Core/Text/SourceText.hpp"
#include "polyglot/CodeAnalysis/Text/TextSpan.hpp"
#include "CodeAnalysis/Core/Text/TextUtilities.hpp"
#include <cassert>
#include <algorithm>
#include <vector>

namespace polyglot::CodeAnalysis
{

// ----------------------------------------------
// TextLine
// ----------------------------------------------

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

// ----------------------------------------------
// TextLineCollection
// ----------------------------------------------

TextLineCollection::TextLineCollection(SourceText* sourceText) noexcept
    : _lineStarts{},
      _pSourceText{sourceText},
      _lastLineNumber{}
{}

pg_size binarySearch(const std::vector<pg_size>& container,
                     const pg_size value)
{
    pg_size low{};
    pg_size high{ container.size() - 1 };

    while (low <= high)
    {
        pg_size middle = low + ((high - low) >> 1);
        pg_size middleValue = container[middle];

        if (middleValue == value)
            return middle;
        else if (middleValue > value)
            high = middle - 1;
        else
            low = middle + 1;
    }

    return ~low;
}

pg_size TextLineCollection::indexOf(const pg_size position) const noexcept
{
    assert(position <= _pSourceText->length());
    pg_size lineNumber{};
    pg_size lastLineNumber{_lastLineNumber};

    if (position >= _lineStarts[lastLineNumber])
    {
        pg_size limit = std::min(_lineStarts.size(), lastLineNumber + 4);

        for (pg_size i = lastLineNumber; i < limit; i++)
        {
            if (position < _lineStarts[i])
            {
                lineNumber = i - 1;
                _lastLineNumber = lineNumber;
                return lineNumber;
            }
        }
    }

    lineNumber = binarySearch(_lineStarts, position);

    if (lineNumber == 0)
        lineNumber = (~lineNumber) - 1;

    _lastLineNumber = lineNumber;
    return lineNumber;
}

TextLine TextLineCollection::operator[](const pg_size index) const noexcept
{
    assert(index < _lineStarts.size());
    const pg_size start = _lineStarts[index];

    if (index == _lineStarts.size() - 1)
    {
        TextSpan textSpan = TextSpan::fromBounds(start, _pSourceText->length());
        return TextLine::fromSpan(_pSourceText, textSpan);
    }
    else
    {
        const pg_size end = _lineStarts[index + 1];
        TextSpan textSpan = TextSpan::fromBounds(start, end);
        return TextLine::fromSpan(_pSourceText, textSpan);
    }
}

TextLine TextLineCollection::textLineFrom(const pg_size position) const noexcept
{
    return (*this)[indexOf(position)];
}

LinePosition TextLineCollection::linePositionFrom(const pg_size position) const noexcept
{
    const TextLine textLine = textLineFrom(position);
    return LinePosition{textLine.lineNumber(), position - textLine.start()};
}

LinePositionSpan TextLineCollection::linePositionSpanFrom(const TextSpan& textSpan) const noexcept
{
    LinePosition start = linePositionFrom(textSpan.start());
    LinePosition end = linePositionFrom(textSpan.end());
    return LinePositionSpan{std::move(start), std::move(end)};
}

pg_size TextLineCollection::positionFrom(const LinePosition& linePosition) const noexcept
{
    return textLineFrom(linePosition.line()).start() + linePosition.character();
}

TextSpan TextLineCollection::textSpanFrom(const LinePositionSpan& linePositionSpan) const noexcept
{
    return TextSpan::fromBounds(positionFrom(linePositionSpan.start()), positionFrom(linePositionSpan.end()));
}

void TextLineCollection::parseLineStarts() noexcept
{
    static constexpr pg_size CHAR_BUFFER_SIZE{ 32 * 1024 };

    _lineStarts.clear();
    _lineStarts.reserve(_pSourceText->length() / 100);
    _lineStarts.push_back(0);

    if (_pSourceText->length() == 0)
        return;

    bool lastWasCR{false};
    pg_size position{};
    const pg_size length = _pSourceText->length();
    auto ptrCharBuffer = std::make_unique<std::vector<char>>(CHAR_BUFFER_SIZE);

    auto parseContent = [&, this](const pg_size& contentLength)
    {
        pg_size index{};

        if (lastWasCR)
        {
            if (contentLength > 0 && (*ptrCharBuffer)[0] == '\n')
                index++;

            _lineStarts.emplace_back(position + index);
            lastWasCR = false;
        }

        while (index < contentLength)
        {
            const char character = (*ptrCharBuffer)[index];
            index++;

            if (character >= 32 && character < 127)
                continue;

            if (character == '\r')
            {
                if (index < contentLength && (*ptrCharBuffer)[index] == '\n')
                    index++;
                else if (index >= contentLength)
                {
                    lastWasCR = true;
                    continue;
                }
            }
            else if (!isAnyLineBreakCharacter(character))
                continue;

            _lineStarts.emplace_back(position + index);
        }
    };

    while (position < length)
    {
        const pg_size contentLength = std::min(length - position, ptrCharBuffer->size());
        _pSourceText->copyTo(position, *ptrCharBuffer, 0, contentLength);
        parseContent(contentLength);
        position += contentLength;
    }
}

// ----------------------------------------------
// SourceText
// ----------------------------------------------

SourceText::SourceText(std::string filename,
                       std::string sourceText) noexcept
    : _filename{std::move(filename)},
      _sourceText{std::move(sourceText)},
      _lineStarts{this}
{}

pg_size SourceText::length() const noexcept
{
    return _sourceText.length();
}

std::string_view SourceText::content() const noexcept
{
    return _sourceText;
}

pg_size SourceText::indexOf(const pg_size position) const noexcept
{
    return _lineStarts.indexOf(position);
}

void SourceText::parseLineStarts() noexcept
{
    _lineStarts.parseLineStarts();
}

const char& SourceText::operator[](const pg_size index) const noexcept
{
    return _sourceText[index];
}

std::string_view SourceText::toString(const TextSpan& textSpan) const noexcept
{
    assert(textSpan.end() <= length());

    if (textSpan.start() == 0 && textSpan.length() == length())
        return _sourceText;

    return std::string_view{_sourceText}.substr(textSpan.start(), textSpan.length());
}

std::string_view SourceText::toString(const pg_size start,
                                      const pg_size length) const noexcept
{
    assert(start <= this->length());
    assert(start + length <= this->length());

    if (start == 0 && length == this->length())
        return _sourceText;

    return std::string_view{_sourceText}.substr(start, length);
}

void SourceText::copyTo(const pg_size sourceIndex,
                        std::vector<char>& destination,
                        const pg_size destinationIndex,
                        const pg_size count) const noexcept
{
    std::copy(std::cbegin(_sourceText) + static_cast<std::vector<char>::difference_type>(sourceIndex),
              std::cbegin(_sourceText) + static_cast<std::vector<char>::difference_type>(sourceIndex + count),
              std::begin(destination) + static_cast<std::vector<char>::difference_type>(destinationIndex));
}

bool operator==(const SourceText& lhs,
                const SourceText& rhs) noexcept
{
    return lhs._sourceText == rhs._sourceText;
}

bool operator!=(const SourceText& lhs,
                const SourceText& rhs) noexcept
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os,
                         const SourceText& sourceText) noexcept
{
    os << sourceText._sourceText;
    return os;
}

} // end namespace polyglot::CodeAnalysis
