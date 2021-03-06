#ifndef POLYGLOT_CORE_TEXT_SOURCETEXT_H
#define POLYGLOT_CORE_TEXT_SOURCETEXT_H

#include <memory>
#include <vector>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Text/LinePosition.hpp"
#include "polyglot/Core/Text/LinePositionSpan.hpp"
#include "polyglot/Core/Text/TextSpan.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::Core::Text
{

class TextSpan;
class SourceText;

// ----------------------------------------------
// TextLine
// ----------------------------------------------

class POLYGLOT_API TextLine final
{
public:
    TextLine() noexcept;
    TextLine(const TextLine&) noexcept = default;
    TextLine(TextLine&&) noexcept = default;
    TextLine& operator=(const TextLine&) noexcept = default;
    TextLine& operator=(TextLine&&) noexcept = default;
    inline const SourceText* text() const noexcept { return _pSourceText; }
    pg_size lineNumber() const noexcept;
    inline pg_size start() const noexcept { return _start; }
    pg_size end() const noexcept;
    inline pg_size endIncludingLineBreak() const noexcept { return _endIncludingLineBreak; }
    TextSpan span() const noexcept;
    TextSpan spanIncludingLineBreak() const noexcept;

    static TextLine fromSpan(SourceText* sourceText,
                             TextSpan& textSpan);

    friend bool operator==(const TextLine& lhs,
                           const TextLine& rhs) noexcept;

    friend bool operator!=(const TextLine& lhs,
                           const TextLine& rhs) noexcept;

    friend pg_ostream& operator<<(pg_ostream& os,
                                  const TextLine& textLine) noexcept;

private:
    explicit TextLine(SourceText* sourceText,
                      const pg_size start,
                      const pg_size endIncludingLineBreak) noexcept;

    pg_size lineBreakLength() const noexcept;

private:
    pg_size _start;
    pg_size _endIncludingLineBreak;
    SourceText* _pSourceText;
};

// ----------------------------------------------
// TextLineCollection
// ----------------------------------------------

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

// ----------------------------------------------
// SourceText
// ----------------------------------------------

class POLYGLOT_API SourceText final
{
public:
    SourceText() = delete;

    explicit SourceText(pg_string filename,
                        pg_string sourceText) noexcept;

    SourceText(const SourceText&) noexcept = default;
    SourceText(SourceText&&) noexcept = default;
    SourceText& operator=(const SourceText&) noexcept = default;
    SourceText& operator=(SourceText&&) noexcept = default;
    inline pg_string filename() const noexcept { return _filename; }
    pg_size length() const noexcept;
    pg_string_view content() const noexcept;
    inline const TextLineCollection& textLines() const noexcept { return _lineStarts; }
    pg_size indexOf(const pg_size position) const noexcept;
    void parseLineStarts() noexcept;
    const pg_char& operator[](const pg_size index) const noexcept;
    pg_string_view toString(const TextSpan& textSpan) const noexcept;

    pg_string_view toString(const pg_size start,
                            const pg_size length) const noexcept;

    void copyTo(const pg_size sourceIndex,
                std::vector<pg_char>& destination,
                const pg_size destinationIndex,
                const pg_size count) const noexcept;

    friend bool operator==(const SourceText& lhs,
                           const SourceText& rhs) noexcept;

    friend bool operator!=(const SourceText& lhs,
                           const SourceText& rhs) noexcept;

    friend pg_ostream& operator<<(pg_ostream& os,
                                  const SourceText& sourceText) noexcept;

private:
    pg_string _filename;
    pg_string _sourceText;
    TextLineCollection _lineStarts;
};

using SourceTextPtr = std::shared_ptr<SourceText>;

} // end namespace polyglot::Core::Text

#endif // POLYGLOT_CORE_TEXT_SOURCETEXT_H
