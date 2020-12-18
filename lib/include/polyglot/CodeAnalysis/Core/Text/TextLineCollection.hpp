#ifndef POLYGLOT_CODEANALYSIS_CORE_TEXT_TEXTLINECOLLECTION_H
#define POLYGLOT_CODEANALYSIS_CORE_TEXT_TEXTLINECOLLECTION_H

#include <vector>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Text/LinePosition.hpp"
#include "polyglot/CodeAnalysis/Core/Text/LinePositionSpan.hpp"
#include "polyglot/CodeAnalysis/Core/Text/TextLine.hpp"
#include "polyglot/CodeAnalysis/Core/Text/TextSpan.hpp"

namespace polyglot::CodeAnalysis
{

class SourceText;

class POLYGLOT_API TextLineCollection final
{
public:
    TextLineCollection() = delete;
    explicit TextLineCollection(SourceText* sourceText) noexcept;
    TextLineCollection(const TextLineCollection&) noexcept = default;
    TextLineCollection(TextLineCollection&&) noexcept = default;
    TextLineCollection& operator=(const TextLineCollection&) noexcept = default;
    TextLineCollection& operator=(TextLineCollection&&) noexcept = default;
    inline pg_size count() const noexcept { return _lineStarts.size(); }
    pg_size indexOf(const pg_size position) const noexcept;
    TextLine operator[](const pg_size index) const noexcept;
    TextLine textLineFrom(const pg_size position) const noexcept;
    LinePosition linePositionFrom(const pg_size position) const noexcept;
    LinePositionSpan linePositionSpanFrom(const TextSpan& textSpan) const noexcept;
    pg_size positionFrom(const LinePosition& linePosition) const noexcept;
    TextSpan textSpanFrom(const LinePositionSpan& linePositionSpan) const noexcept;
    void parseLineStarts() noexcept;

private:
    std::vector<pg_size> _lineStarts;
    SourceText* _pSourceText;
    mutable pg_size _lastLineNumber;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_TEXT_TEXTLINECOLLECTION_H
