#include "polyglot/CodeAnalysis/Core/Parser.hpp"

#ifdef COLLECT_BENCHMARKS
#include "polyglot/CodeAnalysis/Core/LexerBenchmark.hpp"
#endif

namespace polyglot::CodeAnalysis
{

Parser::Parser(std::unique_ptr<Lexer> lexer) noexcept
    : _ptrLexer{std::move(lexer)},
      _tokens{},
      _position{}
{}

Parser::~Parser() noexcept
{}

void Parser::lex() noexcept
{
    SyntaxKind tokenKind = SyntaxKind::EndOfFileToken;
    pg_size tokenCount{};

    do
    {
        auto ptrToken = _ptrLexer->nextToken();
        tokenKind = ptrToken->syntaxKind();
        tokenCount++;
    }
    while (tokenKind != SyntaxKind::EndOfFileToken && tokenKind != SyntaxKind::None);

#ifdef COLLECT_BENCHMARKS
    _ptrLexer->benchmark().setTokenCount(tokenCount);
#endif
}

} // end namespace polyglot::CodeAnalysis
