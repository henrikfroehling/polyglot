#include "polyglot/CodeAnalysis/Core/Text/SlidingTextWindow.hpp"
#include "polyglot/CodeAnalysis/Core/Lexer.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SourceText.hpp"
#include <algorithm>
#include <limits>

namespace polyglot::CodeAnalysis
{

constexpr pg_size DEFAULT_WINDOW_LENGTH{2048};

SlidingTextWindow::SlidingTextWindow(SourceText* sourceText) noexcept
    : _pSourceText{sourceText},
      _basis{},
      _offset{},
      _textEnd{sourceText->length()},
      _characterWindow(DEFAULT_WINDOW_LENGTH),
      _characterWindowCount{},
      _lexemeStart{}
{}

void SlidingTextWindow::start() noexcept
{
    _lexemeStart = _offset;
    moreCharacters();
}

void SlidingTextWindow::reset(const pg_size position) noexcept
{
    const pg_size relativePosition = position - _basis;

    if (relativePosition <= _characterWindowCount)
        _offset = relativePosition;
    else
    {
        pg_size amountToRead = std::min(_pSourceText->length(), position + _characterWindow.size()) - position;
        amountToRead = std::max(amountToRead, static_cast<pg_size>(0));

        if (amountToRead > 0)
            _pSourceText->copyTo(position, _characterWindow, 0, amountToRead);

        _lexemeStart = 0;
        _offset = 0;
        _basis = position;
        _characterWindowCount = amountToRead;
    }
}

bool SlidingTextWindow::isReallyAtEnd() const noexcept
{
    return _offset >= _characterWindowCount && position() >= _textEnd;
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
    if (_offset >= _characterWindowCount && !moreCharacters())
        return Lexer::INVALID_CHARACTER;

    return _characterWindow[_offset];
}

char SlidingTextWindow::peekCharacter(const pg_size offset) noexcept
{
    advanceCharacter(offset);
    char character{};

    if (_offset >= _characterWindowCount && !moreCharacters())
        character = Lexer::INVALID_CHARACTER;
    else
        character = _characterWindow[_offset];

    reset(position());
    return character;
}

char SlidingTextWindow::peekPreviousCharacter(const pg_size offset) noexcept
{
    char character{};
    const pg_size position = _offset - offset;

    if (position >= _characterWindowCount)
        character = Lexer::INVALID_CHARACTER;
    else
        character = _characterWindow[position];

    return character;
}

std::string_view SlidingTextWindow::text() const noexcept
{
    pg_size offset = lexemeStartPosition() - _basis;

    switch (width())
    {
        case 0:
            return "";
        case 1:
        {
            if (_characterWindow[offset] == ' ')
                return " ";

            if (_characterWindow[offset] == '\n')
                return "\n";

            break;
        }
        case 2:
        {
            char firstCharacter = _characterWindow[offset];

            if (firstCharacter == '\r' && _characterWindow[offset + 1] == '\n')
                return "\r\n";

            if (firstCharacter == '/' && _characterWindow[offset + 1] == '/')
                return "//";

            break;
        }
        case 3:
        {
            if (_characterWindow[offset] == '/' && _characterWindow[offset + 1] == '/' && _characterWindow[offset + 2] == ' ')
                return "//";

            break;
        }
    }

    return std::string_view{_characterWindow.data() + offset, width()};
}

bool SlidingTextWindow::moreCharacters() noexcept
{
    if (_offset >= _characterWindowCount)
    {
        if (position() >= _textEnd)
            return false;

        if (_lexemeStart > (_characterWindowCount / 4))
        {
            _characterWindowCount -= _lexemeStart;
            _offset -= _lexemeStart;
            _basis += _lexemeStart;
            _lexemeStart = 0;
        }

        if (_characterWindowCount >= _characterWindow.size())
            _characterWindow.reserve(_characterWindow.size() * 2);

        const pg_size amountToRead = std::min(_textEnd - (_basis + _characterWindowCount), _characterWindow.size() - _characterWindowCount);
        _pSourceText->copyTo(_basis + _characterWindowCount, _characterWindow, _characterWindowCount, amountToRead);
        _characterWindowCount += amountToRead;
        return amountToRead > 0;
    }

    return true;
}

} // end namespace polyglot::CodeAnalysis
