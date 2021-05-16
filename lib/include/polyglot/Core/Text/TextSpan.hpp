#ifndef POLYGLOT_CORE_TEXT_TEXTSPAN_H
#define POLYGLOT_CORE_TEXT_TEXTSPAN_H

#include <ostream>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::Core::Text
{

class POLYGLOT_API TextSpan final
{
public:
    TextSpan() noexcept = default;

    explicit TextSpan(const pg_size start,
                      const pg_size lenght) noexcept;

    TextSpan(const TextSpan&) noexcept = default;
    TextSpan(TextSpan&&) noexcept = default;
    TextSpan& operator=(const TextSpan&) noexcept = default;
    TextSpan& operator=(TextSpan&&) noexcept = default;
    inline pg_size start() const noexcept { return _start; }
    inline pg_size length() const noexcept { return _length; }
    inline pg_size end() const noexcept { return _start + _length; }
    inline bool isEmpty() const noexcept { return _length == 0; }
    bool contains(const pg_size position) const noexcept;
    bool contains(const TextSpan& otherTextSpan) const noexcept;
    bool overlapsWith(const TextSpan& otherTextSpan) const noexcept;
    TextSpan overlapOf(const TextSpan& otherTextSpan) const noexcept;
    bool intersectsWith(const pg_size position) const noexcept;
    bool intersectsWith(const TextSpan& otherTextSpan) const noexcept;
    TextSpan intersectionOf(const TextSpan& otherTextSpan) const noexcept;

    static TextSpan fromBounds(const pg_size start,
                               const pg_size end) noexcept;

    friend bool operator==(const TextSpan& lhs,
                           const TextSpan& rhs) noexcept;

    friend bool operator!=(const TextSpan& lhs,
                           const TextSpan& rhs) noexcept;

    friend std::ostream& operator<<(std::ostream& os,
                                    const TextSpan& textSpan) noexcept;

private:
    pg_size _start;
    pg_size _length;
};

} // end namespace polyglot::Core::Text

#endif // POLYGLOT_CORE_TEXT_TEXTSPAN_H
