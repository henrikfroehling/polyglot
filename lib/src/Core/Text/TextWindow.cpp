#include "Core/Text/TextWindow.hpp"
#include <cassert>
#include <algorithm>
#include <limits>
#include "Core/Parser/Lexer.hpp"

namespace polyglot::Core::Text
{

using polyglot::Core::Parser::Lexer;

constexpr pg_size DEFAULT_WINDOW_LENGTH{2048};

TextWindow::TextWindow(SourceTextPtr sourceText) noexcept
    : _ptrSourceText{sourceText},
      _basis{},
      _offset{},
      _textEnd{sourceText->length()},
      _lexemeStart{}
{}

void TextWindow::reset(const pg_size position) noexcept
{
    const pg_size relativePosition = position - _basis;

    if (relativePosition <= _textEnd)
        _offset = relativePosition;
    else
    {
        _lexemeStart = 0;
        _offset = 0;
        _basis = position;
    }
}

void TextWindow::resetToLastPosition() noexcept
{
    if (position() > 0)
        reset(position() - 1);
}

bool TextWindow::isAtEnd() const noexcept
{
    return position() >= _textEnd;
}

pg_string_view TextWindow::substring(const pg_size start,
                                     const pg_size length) const noexcept
{
    return _ptrSourceText->content().substr(start, length);
}

pg_string_view TextWindow::substringUntilCurrentPosition(const pg_size start) const noexcept
{
    assert(start <= position());
    return _ptrSourceText->content().substr(start, position() - start);
}

pg_char TextWindow::nextCharacter() noexcept
{
    const pg_char character = peekCharacter();

    if (character != Lexer::INVALID_CHARACTER)
        advanceCharacter();

    return character;
}

pg_char TextWindow::peekCharacter() noexcept
{
    if (_offset >= _textEnd)
        return Lexer::INVALID_CHARACTER;

    return (*_ptrSourceText)[_offset];
}

pg_char TextWindow::peekCharacter(const pg_size offset) noexcept
{
    const pg_size currentOffset{_offset};
    advanceCharacter(offset);
    pg_char character{};

    if (_offset >= _textEnd)
        character = Lexer::INVALID_CHARACTER;
    else
        character = (*_ptrSourceText)[_offset];

    reset(currentOffset);
    return character;
}

pg_char TextWindow::peekPreviousCharacter(const pg_size offset) noexcept
{
    pg_char character{};
    const pg_size position = _offset - offset;

    if (position >= _textEnd)
        character = Lexer::INVALID_CHARACTER;
    else
        character = (*_ptrSourceText)[position];

    return character;
}

pg_string_view TextWindow::lexemeText() const noexcept
{
    pg_size offset = lexemeStartPosition() - _basis;

    switch (width())
    {
        case 0:
            return L"";
        case 1:
        {
            if ((*_ptrSourceText)[offset] == L' ')
                return L" ";

            if ((*_ptrSourceText)[offset] == L'\n')
                return L"\n";

            break;
        }
        case 2:
        {
            pg_char firstCharacter = (*_ptrSourceText)[offset];

            if (firstCharacter == L'\r' && (*_ptrSourceText)[offset + 1] == L'\n')
                return L"\r\n";

            if (firstCharacter == L'/' && (*_ptrSourceText)[offset + 1] == L'/')
                return L"//";

            break;
        }
        case 3:
        {
            if ((*_ptrSourceText)[offset] == L'/' && (*_ptrSourceText)[offset + 1] == L'/' && (*_ptrSourceText)[offset + 2] == L' ')
                return L"//";

            break;
        }
    }

    return pg_string_view{_ptrSourceText->content().data() + offset, width()};
}

} // end namespace polyglot::Core::Text
