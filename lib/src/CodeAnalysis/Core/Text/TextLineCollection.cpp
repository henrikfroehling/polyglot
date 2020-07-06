#include "polyglot/CodeAnalysis/Core/Text/TextLineCollection.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SourceText.hpp"
#include "polyglot/CodeAnalysis/Core/Text/TextSpan.hpp"
#include "polyglot/CodeAnalysis/Core/Text/TextUtilities.hpp"
#include <cassert>
#include <algorithm>
#include <memory>

namespace polyglot::CodeAnalysis
{

TextLineCollection::TextLineCollection(const SourceText* sourceText) noexcept
    : _lineStarts{},
      _pSourceText{sourceText},
      _lastLineNumber{}
{}

TextLineCollection::TextLineCollection(const TextLineCollection& other) noexcept
    : _lineStarts{other._lineStarts},
      _pSourceText{other._pSourceText},
      _lastLineNumber{other._lastLineNumber}
{}

TextLineCollection::TextLineCollection(TextLineCollection&& other) noexcept
    : _lineStarts{std::move(other._lineStarts)},
      _pSourceText{std::move(other._pSourceText)},
      _lastLineNumber{std::move(other._lastLineNumber)}
{}

TextLineCollection& TextLineCollection::operator=(TextLineCollection other) noexcept
{
    swap(*this, other);
    return *this;
}

pg_size binarySearch(const std::vector<pg_size>& container,
                     const pg_size value)
{
    pg_size low{};
    pg_size high{container.size() - 1};

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

TextLine TextLineCollection::lineFromPosition(const pg_size position) const noexcept
{
    return (*this)[indexOf(position)];
}

void TextLineCollection::parseLineStarts() noexcept
{
    static constexpr pg_size CHAR_BUFFER_SIZE{32 * 1024};

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

            if (character >= 32 && character < 127 && character != '\r')
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

void swap(TextLineCollection& lhs,
          TextLineCollection& rhs) noexcept
{
    using std::swap;
    swap(lhs._lineStarts, rhs._lineStarts);
    swap(lhs._pSourceText, rhs._pSourceText);
    swap(lhs._lastLineNumber, rhs._lastLineNumber);
}

} // end namespace polyglot::CodeAnalysis
