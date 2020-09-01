#include "polyglot/CodeAnalysis/Core/Text/SlidingTextWindow.hpp"
#include "polyglot/CodeAnalysis/Core/Lexer.hpp"
#include <algorithm>
#include <limits>

namespace polyglot::CodeAnalysis
{

constexpr pg_size DEFAULT_WINDOW_LENGTH{2048};

SlidingTextWindow::SlidingTextWindow(SourceTextPtr sourceText) noexcept
    : _ptrSourceText{sourceText},
      _basis{},
      _offset{},
      _textEnd{sourceText->length()},
      _lexemeStart{}
{}

void SlidingTextWindow::reset(const pg_size position) noexcept
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

bool SlidingTextWindow::isAtEnd() const noexcept
{
    return position() >= _textEnd;
}

char SlidingTextWindow::nextCharacter() noexcept
{
    const char character = peekCharacter();

    if (character != Lexer::INVALID_CHARACTER)
        advanceCharacter();

    return character;
}

char SlidingTextWindow::peekCharacter() noexcept
{
    if (_offset >= _textEnd)
        return Lexer::INVALID_CHARACTER;

    return (*_ptrSourceText)[_offset];
}

char SlidingTextWindow::peekCharacter(const pg_size offset) noexcept
{
    advanceCharacter(offset);
    char character{};

    if (_offset >= _textEnd)
        character = Lexer::INVALID_CHARACTER;
    else
        character = (*_ptrSourceText)[_offset];

    reset(position());
    return character;
}

char SlidingTextWindow::peekPreviousCharacter(const pg_size offset) noexcept
{
    char character{};
    const pg_size position = _offset - offset;

    if (position >= _textEnd)
        character = Lexer::INVALID_CHARACTER;
    else
        character = (*_ptrSourceText)[position];

    return character;
}

std::string_view SlidingTextWindow::lexemeText() const noexcept
{
    pg_size offset = lexemeStartPosition() - _basis;

    switch (width())
    {
        case 0:
            return "";
        case 1:
        {
            if ((*_ptrSourceText)[offset] == ' ')
                return " ";

            if ((*_ptrSourceText)[offset] == '\n')
                return "\n";

            break;
        }
        case 2:
        {
            char firstCharacter = (*_ptrSourceText)[offset];

            if (firstCharacter == '\r' && (*_ptrSourceText)[offset + 1] == '\n')
                return "\r\n";

            if (firstCharacter == '/' && (*_ptrSourceText)[offset + 1] == '/')
                return "//";

            break;
        }
        case 3:
        {
            if ((*_ptrSourceText)[offset] == '/' && (*_ptrSourceText)[offset + 1] == '/' && (*_ptrSourceText)[offset + 2] == ' ')
                return "//";

            break;
        }
    }

    return std::string_view{_ptrSourceText->content().data() + offset, width()};
}

} // end namespace polyglot::CodeAnalysis
