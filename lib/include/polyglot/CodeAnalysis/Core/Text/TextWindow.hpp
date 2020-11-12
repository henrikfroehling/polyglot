#ifndef POLYGLOT_CODEANALYSIS_CORE_TEXT_TEXTWINDOW_H
#define POLYGLOT_CODEANALYSIS_CORE_TEXT_TEXTWINDOW_H

#include <string_view>
#include <vector>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SourceText.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API TextWindow final
{
public:
    TextWindow() = delete;
    explicit TextWindow(SourceTextPtr sourceText) noexcept;
    TextWindow(const TextWindow&) noexcept = default;
    TextWindow(TextWindow&&) noexcept = default;
    TextWindow& operator=(const TextWindow&) noexcept = default;
    TextWindow& operator=(TextWindow&&) noexcept = default;
    inline pg_size position() const noexcept { return _basis + _offset; }
    inline pg_size offset() const noexcept { return _offset; }
    inline pg_size lexemeStartPosition() const noexcept { return _basis + _lexemeStart; }
    inline pg_size lexemeRelativeStart() const noexcept { return _lexemeStart; }
    inline pg_size width() const noexcept { return _offset - _lexemeStart; }
    inline void start() noexcept { _lexemeStart = _offset; }
    void reset(const pg_size position) noexcept;
    bool isAtEnd() const noexcept;
    inline std::string_view content() const noexcept { return _ptrSourceText->content(); }
    inline void advanceCharacter(const pg_size n = 1) noexcept { _offset += n; }
    char nextCharacter() noexcept;
    char peekCharacter() noexcept;
    char peekCharacter(const pg_size offset) noexcept;
    char peekPreviousCharacter(const pg_size offset) noexcept;
    std::string_view lexemeText() const noexcept;

private:
    SourceTextPtr _ptrSourceText;
    pg_size _basis;
    pg_size _offset;
    pg_size _textEnd;
    pg_size _lexemeStart;
};

} // end namespace polyglot::CodeAnaylsis

#endif // POLYGLOT_CODEANALYSIS_CORE_TEXT_TEXTWINDOW_H
