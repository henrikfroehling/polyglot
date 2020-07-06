#ifndef POLYGLOT_CODEANALYSIS_CORE_TEXT_TEXTLINECOLLECTION_H
#define POLYGLOT_CODEANALYSIS_CORE_TEXT_TEXTLINECOLLECTION_H

#include <vector>
#include "polyglot/CodeAnalysis/Core/Text/TextLine.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/polyglot_global.hpp"

namespace polyglot::CodeAnalysis
{

class SourceText;

class POLYGLOT_API TextLineCollection final
{
public:
    TextLineCollection() = delete;
    explicit TextLineCollection(const SourceText* sourceText) noexcept;
    TextLineCollection(const TextLineCollection& other) noexcept;
    TextLineCollection(TextLineCollection&& other) noexcept;
    TextLineCollection& operator=(TextLineCollection other) noexcept;
    inline pg_size count() const noexcept { return _lineStarts.size(); }
    pg_size indexOf(const pg_size position) const noexcept;
    TextLine operator[](const pg_size index) const noexcept;
    TextLine lineFromPosition(const pg_size position) const noexcept;
    void parseLineStarts() noexcept;

    friend void swap(TextLineCollection& lhs,
                     TextLineCollection& rhs) noexcept;

private:
    std::vector<pg_size> _lineStarts;
    const SourceText* _pSourceText;
    mutable pg_size _lastLineNumber;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_TEXT_TEXTLINECOLLECTION_H
