#include "CodeAnalysis/Core/Text/LinePositionSpan.hpp"
#include <cassert>
#include <utility>

namespace polyglot::CodeAnalysis
{

LinePositionSpan::LinePositionSpan(LinePosition start,
                                   LinePosition end) noexcept
    : _start{std::move(start)},
      _end{std::move(end)}
{
    assert(start < end);
}

bool operator==(const LinePositionSpan& lhs,
                const LinePositionSpan& rhs) noexcept
{
    return lhs._start == rhs._start && lhs._end == rhs._end;
}

bool operator!=(const LinePositionSpan& lhs,
                const LinePositionSpan& rhs) noexcept
{
    return !(lhs == rhs);
}

} // end namespace polyglot::CodeAnalysis
