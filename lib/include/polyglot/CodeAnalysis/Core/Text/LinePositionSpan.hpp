#ifndef POLYGLOT_CODEANALYSIS_CORE_TEXT_LINEPOSITIONSPAN_H
#define POLYGLOT_CODEANALYSIS_CORE_TEXT_LINEPOSITIONSPAN_H

#include "polyglot/CodeAnalysis/Core/Text/LinePosition.hpp"

namespace polyglot::CodeAnalysis
{

class LinePositionSpan final
{
public:
    LinePositionSpan() = delete;

    explicit LinePositionSpan(LinePosition start,
                              LinePosition end) noexcept;

    LinePositionSpan(const LinePositionSpan&) noexcept = default;
    LinePositionSpan(LinePositionSpan&&) noexcept = default;
    LinePositionSpan& operator=(const LinePositionSpan&) noexcept = default;
    LinePositionSpan& operator=(LinePositionSpan&&) noexcept = default;
    inline const LinePosition& start() const noexcept { return _start; }
    inline const LinePosition& end() const noexcept { return _end; }

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
