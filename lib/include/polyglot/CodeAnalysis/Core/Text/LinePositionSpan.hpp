#ifndef POLYGLOT_CODEANALYSIS_CORE_TEXT_LINEPOSITIONSPAN_H
#define POLYGLOT_CODEANALYSIS_CORE_TEXT_LINEPOSITIONSPAN_H

#include "polyglot/CodeAnalysis/Core/Text/LinePosition.hpp"
#include "polyglot/polyglot_global.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API LinePositionSpan final
{
public:
    LinePositionSpan() = delete;

    explicit LinePositionSpan(LinePosition start,
                              LinePosition end) noexcept;

    LinePositionSpan(const LinePositionSpan& other) noexcept;
    LinePositionSpan(LinePositionSpan&& other) noexcept;
    LinePositionSpan& operator=(LinePositionSpan other) noexcept;
    inline const LinePosition& start() const noexcept { return _start; }
    inline const LinePosition& end() const noexcept { return _end; }

    friend void swap(LinePositionSpan& lhs,
                     LinePositionSpan& rhs) noexcept;

    friend bool operator==(const LinePositionSpan& lhs,
                           const LinePositionSpan& rhs) noexcept;

    friend bool operator!=(const LinePositionSpan& lhs,
                           const LinePositionSpan& rhs) noexcept;

private:
    LinePosition _start;
    LinePosition _end;
};

} // end namespace polyglot::CodeAnalyis

#endif // POLYGLOT_CODEANALYSIS_CORE_TEXT_LINEPOSITIONSPAN_H
