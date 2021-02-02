#include "polyglot/CodeAnalysis/Text/TextSpan.hpp"
#include <algorithm>

namespace polyglot::CodeAnalysis
{

TextSpan::TextSpan(const pg_size start,
                   const pg_size lenght) noexcept
    : _start{start},
      _length{lenght}
{}

bool TextSpan::contains(const pg_size position) const noexcept
{
    return (position - _start) < _length;
}

bool TextSpan::contains(const TextSpan& otherTextSpan) const noexcept
{
    return otherTextSpan._start >= _start && otherTextSpan.end() <= end();
}

bool TextSpan::overlapsWith(const TextSpan& otherTextSpan) const noexcept
{
    const pg_size maxStart = std::max(_start, otherTextSpan._start);
    const pg_size minEnd = std::min(end(), otherTextSpan.end());
    return maxStart < minEnd;
}

TextSpan TextSpan::overlapOf(const TextSpan& otherTextSpan) const noexcept
{
    const pg_size maxStart = std::max(_start, otherTextSpan._start);
    const pg_size minEnd = std::min(end(), otherTextSpan.end());
    return maxStart < minEnd ? TextSpan::fromBounds(maxStart, minEnd) : TextSpan{};
}

bool TextSpan::intersectsWith(const pg_size position) const noexcept
{
    return (position - _start) <= _length;
}

bool TextSpan::intersectsWith(const TextSpan& otherTextSpan) const noexcept
{
    return otherTextSpan.end() >= _start && otherTextSpan._start <= end();
}

TextSpan TextSpan::intersectionOf(const TextSpan& otherTextSpan) const noexcept
{
    const pg_size maxStart = std::max(_start, otherTextSpan._start);
    const pg_size minEnd = std::min(end(), otherTextSpan.end());
    return maxStart <= minEnd ? TextSpan::fromBounds(maxStart, minEnd) : TextSpan{};
}

TextSpan TextSpan::fromBounds(const pg_size start,
                              const pg_size end) noexcept
{
    return TextSpan{start, end - start};
}

bool operator==(const TextSpan& lhs,
                const TextSpan& rhs) noexcept
{
    return lhs._start == rhs._start && lhs._length == rhs._length;
}

bool operator!=(const TextSpan& lhs,
                const TextSpan& rhs) noexcept
{
    return !(lhs == rhs);
}

} // end namespace polyglot::CodeAnalysis
