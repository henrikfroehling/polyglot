#ifndef POLYGLOT_CODEANALYSIS_CORE_TEXT_TEXTLINE_H
#define POLYGLOT_CODEANALYSIS_CORE_TEXT_TEXTLINE_H

#include <ostream>
#include "polyglot/CodeAnalysis/Core/Text/TextSpan.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/polyglot_global.hpp"

namespace polyglot::CodeAnalysis
{

class SourceText;

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

    friend std::ostream& operator<<(std::ostream& os,
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

} // end namespace polyglot::CodeAnalyis

#endif // POLYGLOT_CODEANALYSIS_CORE_TEXT_TEXTLINE_H
