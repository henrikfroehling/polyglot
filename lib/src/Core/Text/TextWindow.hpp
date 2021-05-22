#ifndef POLYGLOT_CORE_TEXT_TEXTWINDOW_H
#define POLYGLOT_CORE_TEXT_TEXTWINDOW_H

#include <vector>
#include "polyglot/Core/Text/SourceText.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::Core::Text
{

class TextWindow final
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
    inline pg_string_view content() const noexcept { return _ptrSourceText->content(); }

    pg_string_view substring(const pg_size start,
                             const pg_size length) const noexcept;

    pg_string_view substringUntilCurrentPosition(const pg_size start) const noexcept;
    inline void advanceCharacter(const pg_size n = 1) noexcept { _offset += n; }
    pg_char nextCharacter() noexcept;
    pg_char peekCharacter() noexcept;
    pg_char peekCharacter(const pg_size offset) noexcept;
    pg_char peekPreviousCharacter(const pg_size offset) noexcept;
    pg_string_view lexemeText() const noexcept;

private:
    SourceTextPtr _ptrSourceText;
    pg_size _basis;
    pg_size _offset;
    pg_size _textEnd;
    pg_size _lexemeStart;
};

} // end namespace polyglot::Core::Text

#endif // POLYGLOT_CORE_TEXT_TEXTWINDOW_H
