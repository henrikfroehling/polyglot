#include "polyglot/CodeAnalysis/Core/Lexer.hpp"

namespace polyglot::CodeAnalysis
{

Lexer::Lexer(SourceTextPtr sourceText) noexcept
    : _textWindow{std::move(sourceText)},
      _mode{LexerMode::Syntax},
      _lexerCache{this},
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
