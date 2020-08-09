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

int LinePosition::compareTo(const LinePosition& otherLinePosition) const noexcept
{
    const int lineComparison = compare(_line, otherLinePosition._line);
    return lineComparison != 0 ? lineComparison : compare(_character, otherLinePosition._character);
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
