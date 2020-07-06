#include "polyglot/CodeAnalysis/Core/Text/LinePositionSpan.hpp"
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

LinePositionSpan::LinePositionSpan(const LinePositionSpan& other) noexcept
    : _start{other._start},
      _end{other._end}
{}

LinePositionSpan::LinePositionSpan(LinePositionSpan&& other) noexcept
    : _start{std::move(other._start)},
      _end{std::move(other._end)}
{}

LinePositionSpan& LinePositionSpan::operator=(LinePositionSpan other) noexcept
{
    swap(*this, other);
    return *this;
}

void swap(LinePositionSpan& lhs,
          LinePositionSpan& rhs) noexcept
{
    using std::swap;
    swap(lhs._start, rhs._start);
    swap(lhs._end, rhs._end);
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
