#include "polyglot/CodeAnalysis/Core/Parser.hpp"
#include <iostream>

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

    std::cout << "Token Count: " << tokenCount << "\n";

#ifndef NDEBUG
    std::cout << "Lexer Cache Misses: " << _ptrLexer->cacheMisses() << "\n";
    std::cout << "Lexer Cache Hits: " << _ptrLexer->cacheHits() << "\n";
#endif
}

} // end namespace polyglot::CodeAnalysis
