#include "polyglot/CodeAnalysis/Core/Lexer.hpp"

namespace polyglot::CodeAnalysis
{

Lexer::Lexer(const SourceText& sourceText) noexcept
    : _textWindow{sourceText},
      _leadingTriviaCache{},
      _trailingTriviaCache{}
{}

Lexer::~Lexer()
{}

void Lexer::start() noexcept
{
    _textWindow.start();
}

} // end namespace polyglot::CodeAnalysis
