#ifndef POLYGLOT_CODEANALYSIS_CORE_TEXT_SLIDINGTEXTWINDOW_H
#define POLYGLOT_CODEANALYSIS_CORE_TEXT_SLIDINGTEXTWINDOW_H

#include <string_view>
#include <vector>
#include "polyglot/Core/Types.hpp"
#include "polyglot/polyglot_global.hpp"

namespace polyglot::CodeAnalysis
{

class SourceText;

class POLYGLOT_API SlidingTextWindow final
{
public:
    SlidingTextWindow() = delete;
    explicit SlidingTextWindow(SourceText* sourceText) noexcept;
    SlidingTextWindow(const SlidingTextWindow&) noexcept = default;
    SlidingTextWindow(SlidingTextWindow&&) noexcept = default;
    SlidingTextWindow& operator=(const SlidingTextWindow&) noexcept = default;
    SlidingTextWindow& operator=(SlidingTextWindow&&) noexcept = default;
    inline pg_size position() const noexcept { return _basis + _offset; }
    inline pg_size offset() const noexcept { return _offset; }
    inline const std::vector<char>& characterWindow() const noexcept { return _characterWindow; }
    inline pg_size characterWindowCount() const noexcept { return _characterWindowCount; }
    inline pg_size lexemeStartPosition() const noexcept { return _basis + _lexemeStart; }
    inline pg_size lexemeRelativeStart() const noexcept { return _lexemeStart; }
    inline pg_size width() const noexcept { return _offset - _lexemeStart; }
    void start() noexcept;
    void reset(const pg_size position) noexcept;
    bool isReallyAtEnd() const noexcept;

    inline void advanceCharacter(const pg_size n = 1,
                                 const bool setLexemeStart = false) noexcept
    {
        _offset += n;

        if (setLexemeStart)
            _lexemeStart = _offset;
    }

    char nextCharacter() noexcept;
    char peekCharacter() noexcept;
    char peekCharacter(const pg_size offset) noexcept;
    char peekPreviousCharacter(const pg_size offset) noexcept;
    std::string_view text() const noexcept;

private:
    bool moreCharacters() noexcept;

private:
    SourceText* _pSourceText;
    pg_size _basis;
    pg_size _offset;
    pg_size _textEnd;
    std::vector<char> _characterWindow;
    pg_size _characterWindowCount;
    pg_size _lexemeStart;
};

} // end namespace polyglot::CodeAnaylsis

#endif // POLYGLOT_CODEANALYSIS_CORE_TEXT_SLIDINGTEXTWINDOW_H
