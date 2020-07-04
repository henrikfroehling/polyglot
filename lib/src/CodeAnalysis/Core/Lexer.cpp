#include "polyglot/CodeAnalysis/Core/Lexer.hpp"

namespace polyglot::CodeAnalysis
{

Lexer::Lexer(std::string_view code) noexcept
    : _code{std::move(code)},
      _position{0}
{}

Lexer::~Lexer()
{}

char Lexer::current() const noexcept
{
    if (_position >= _code.length())
        return '\0';

    return _code[_position];
}

} // end namespace polyglot::CodeAnalysis
