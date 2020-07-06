#include "polyglot/CodeAnalysis/Core/Text/LinePosition.hpp"
#include <utility>

namespace polyglot::CodeAnalysis
{

constexpr int compare(const pg_size lhs,
                      const pg_size rhs) noexcept
{
    return lhs < rhs ? -1 : (lhs > rhs ? 1 : 0);
}

LinePosition::LinePosition(const pg_size line,
                           const pg_size character) noexcept
    : _line{line},
      _character{character}
{}

LinePosition::LinePosition(const LinePosition& other) noexcept
    : _line{other._line},
      _character{other._character}
{}

LinePosition::LinePosition(LinePosition&& other) noexcept
    : _line{std::move(other._line)},
      _character{std::move(other._character)}
{}

LinePosition& LinePosition::operator=(LinePosition other) noexcept
{
    swap(*this, other);
    return *this;
}

int LinePosition::compareTo(const LinePosition& otherLinePosition) const noexcept
{
    const int lineComparison = compare(_line, otherLinePosition._line);
    return lineComparison != 0 ? lineComparison : compare(_character, otherLinePosition._character);
}

void swap(LinePosition& lhs,
          LinePosition& rhs) noexcept
{
    using std::swap;
    swap(lhs._line, rhs._line);
    swap(lhs._character, rhs._character);
}

bool operator==(const LinePosition& lhs,
                const LinePosition& rhs) noexcept
{
    return lhs._line == rhs._line && lhs._character == rhs._character;
}

bool operator!=(const LinePosition& lhs,
                const LinePosition& rhs) noexcept
{
    return !(lhs == rhs);
}

bool operator<(const LinePosition& lhs,
               const LinePosition& rhs) noexcept
{
    return lhs.compareTo(rhs) < 0;
}

bool operator>(const LinePosition& lhs,
               const LinePosition& rhs) noexcept
{
    return lhs.compareTo(rhs) > 0;
}

bool operator<=(const LinePosition& lhs,
                const LinePosition& rhs) noexcept
{
    return lhs.compareTo(rhs) <= 0;
}

bool operator>=(const LinePosition& lhs,
                const LinePosition& rhs) noexcept
{
    return lhs.compareTo(rhs) >= 0;
}

} // end namespace polyglot::CodeAnalysis
