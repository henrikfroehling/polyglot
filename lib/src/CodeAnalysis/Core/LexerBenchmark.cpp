#include "polyglot/CodeAnalysis/Core/LexerBenchmark.hpp"

namespace polyglot::CodeAnalysis
{

LexerBenchmark::LexerBenchmark() noexcept
    : _filename{},
      _duration{},
      _lineCount{},
      _tokenCount{},
      _cacheMisses{},
      _cacheHits{}
{}

std::ostream& operator<<(std::ostream& os,
                         const LexerBenchmark& benchmark) noexcept
{
    os << "Filename: " << benchmark._filename << "\n";
    os << "Line Count: " << benchmark._lineCount << "\n";
    os << "Lexing took " << benchmark._duration << "ms\n";
    os << "Token Count: " << benchmark._tokenCount << "\n";
    os << "Lexer Cache Misses: " << benchmark._cacheMisses << "\n";
    os << "Lexer Cache Hits: " << benchmark._cacheHits << "\n";
    return os;
}

} // end namespace polyglot::CodeAnalysis
