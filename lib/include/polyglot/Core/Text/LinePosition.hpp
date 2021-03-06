#ifndef POLYGLOT_CORE_TEXT_LINEPOSITION_H
#define POLYGLOT_CORE_TEXT_LINEPOSITION_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::Core::Text
{

class POLYGLOT_API LinePosition final
{
public:
    LinePosition() noexcept = default;

    explicit LinePosition(const pg_size line,
                          const pg_size character) noexcept;

    LinePosition(const LinePosition&) noexcept = default;
    LinePosition(LinePosition&&) noexcept = default;
    LinePosition& operator=(const LinePosition&) noexcept = default;
    LinePosition& operator=(LinePosition&&) noexcept = default;
    inline pg_size line() const noexcept { return _line; }
    inline pg_size character() const noexcept { return _character; }
    int compareTo(const LinePosition& otherLinePosition) const noexcept;

    friend bool operator==(const LinePosition& lhs,
                           const LinePosition& rhs) noexcept;

    friend bool operator!=(const LinePosition& lhs,
                           const LinePosition& rhs) noexcept;

    friend bool operator<(const LinePosition& lhs,
                          const LinePosition& rhs) noexcept;

    friend bool operator>(const LinePosition& lhs,
                          const LinePosition& rhs) noexcept;

    friend bool operator<=(const LinePosition& lhs,
                           const LinePosition& rhs) noexcept;

    friend bool operator>=(const LinePosition& lhs,
                           const LinePosition& rhs) noexcept;

private:
    pg_size _line;
    pg_size _character;
};

} // end namespace polyglot::Core::Text

#endif // POLYGLOT_CORE_TEXT_LINEPOSITION_H
