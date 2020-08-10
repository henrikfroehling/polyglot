#ifndef POLYGLOT_CODEANALYSIS_CORE_TEXT_SOURCETEXT_H
#define POLYGLOT_CODEANALYSIS_CORE_TEXT_SOURCETEXT_H

#include <ostream>
#include <string>
#include <string_view>
#include <vector>
#include "polyglot/CodeAnalysis/Core/Text/TextLineCollection.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/polyglot_global.hpp"

namespace polyglot::CodeAnalysis
{

class TextSpan;

class POLYGLOT_API SourceText final
{
public:
    SourceText() = delete;

    explicit SourceText(std::string filename,
                        std::string sourceText) noexcept;

    SourceText(const SourceText&) noexcept = default;
    SourceText(SourceText&&) noexcept = default;
    SourceText& operator=(const SourceText&) noexcept = default;
    SourceText& operator=(SourceText&&) noexcept = default;
    inline std::string filename() const noexcept { return _filename; }
    pg_size length() const noexcept;
    std::string_view content() const noexcept;
    pg_size indexOf(const pg_size position) const noexcept;
    void parseLineStarts() noexcept;
    const char& operator[](const pg_size index) const noexcept;
    std::string_view toString(const TextSpan& textSpan) const noexcept;

    std::string_view toString(const pg_size start,
                              const pg_size length) const noexcept;

    void copyTo(const pg_size sourceIndex,
                std::vector<char>& destination,
                const pg_size destinationIndex,
                const pg_size count) const noexcept;

    friend bool operator==(const SourceText& lhs,
                           const SourceText& rhs) noexcept;

    friend bool operator!=(const SourceText& lhs,
                           const SourceText& rhs) noexcept;

    friend std::ostream& operator<<(std::ostream& os,
                                    const SourceText& sourceText) noexcept;

private:
    std::string _filename;
    std::string _sourceText;
    TextLineCollection _lineStarts;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_TEXT_SOURCETEXT_H
