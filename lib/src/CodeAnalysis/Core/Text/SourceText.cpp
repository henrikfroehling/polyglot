#include "polyglot/CodeAnalysis/Core/Text/SourceText.hpp"
#include "polyglot/CodeAnalysis/Core/Text/TextSpan.hpp"
#include <cassert>
#include <algorithm>
#include <vector>

namespace polyglot::CodeAnalysis
{

SourceText::SourceText(std::string sourceText) noexcept
    : _sourceText{std::move(sourceText)},
      _lineStarts{this}
{}

SourceText::SourceText(const SourceText& other) noexcept
    : _sourceText{other._sourceText},
      _lineStarts{other._lineStarts}
{}

SourceText::SourceText(SourceText&& other) noexcept
    : _sourceText{std::move(other._sourceText)},
      _lineStarts{std::move(other._lineStarts)}
{}

SourceText& SourceText::operator=(SourceText other) noexcept
{
    swap(*this, other);
    return *this;
}

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

    return _sourceText.substr(textSpan.start(), textSpan.length());
}

std::string_view SourceText::toString(const pg_size start,
                                      const pg_size length) const noexcept
{
    assert(start <= this->length());
    assert(start + length <= this->length());

    if (start == 0 && length == this->length())
        return _sourceText;

    return _sourceText.substr(start, length);
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

void swap(SourceText& lhs,
          SourceText& rhs) noexcept
{
    using std::swap;
    swap(lhs._sourceText, rhs._sourceText);
    swap(lhs._lineStarts, rhs._lineStarts);
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
