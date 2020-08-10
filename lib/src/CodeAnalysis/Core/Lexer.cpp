#include "polyglot/CodeAnalysis/Core/Lexer.hpp"

namespace polyglot::CodeAnalysis
{

Lexer::Lexer(SourceText* sourceText) noexcept
    : _textWindow{sourceText},
      _lexerCache{},
      _leadingTrivia{},
      _trailingTrivia{}
{}

Lexer::~Lexer()
{}

void Lexer::start() noexcept
{
    _textWindow.start();
}

} // end namespace polyglot::CodeAnalysis
