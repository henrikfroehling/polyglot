#include "polyglot/CodeAnalysis/Core/Lexer.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SourceText.hpp"

namespace polyglot::CodeAnalysis
{

Lexer::Lexer(SourceText* sourceText) noexcept
    : _textWindow{sourceText},
      _lexerCache{this},
      _leadingTrivia{},
      _trailingTrivia{},
      _benchmark{}
{
    _benchmark.setFilename(sourceText->filename());
}

Lexer::~Lexer()
{}

void Lexer::start() noexcept
{
    _textWindow.start();
}

} // end namespace polyglot::CodeAnalysis
