#include "polyglot/CodeAnalysis/Core/Parser.hpp"
#ifndef NDEBUG
#include <iostream>
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

    do
    {
        auto ptrToken = _ptrLexer->nextToken();
        tokenKind = ptrToken->syntaxKind();

        //if (tokenKind != SyntaxKind::WhitespaceToken)
        //    _tokens.push_back(std::move(ptrToken));
    }
    while (tokenKind != SyntaxKind::EndOfFileToken);

#ifndef NDEBUG
    std::cout << "Lexer Cache Misses: " << _ptrLexer->cacheMisses() << "\n";
    std::cout << "Lexer Cache Hits: " << _ptrLexer->cacheHits() << "\n";
#endif
}

} // end namespace polyglot::CodeAnalysis
