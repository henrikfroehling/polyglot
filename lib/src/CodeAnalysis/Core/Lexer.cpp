#include "polyglot/CodeAnalysis/Core/Lexer.hpp"

namespace polyglot::CodeAnalysis
{

Lexer::Lexer(SourceTextPtr sourceText) noexcept
    : _textWindow{sourceText},
      _lexerCache{this},
      _leadingTrivia{},
      _trailingTrivia{},
      _benchmark{}
{
#ifdef COLLECT_BENCHMARKS
    _benchmark.setFilename(sourceText->filename());
    _benchmark.setLineCount(sourceText->textLines().count());
#endif
}

Lexer::~Lexer()
{}

void Lexer::start() noexcept
{
    _textWindow.start();
}

} // end namespace polyglot::CodeAnalysis
