#include "polyglot/CodeAnalysis/Core/Parser.hpp"

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
    SyntaxToken token{};

    do
    {
        token = _ptrLexer->nextToken();

        if (token.kind != SyntaxKind::WhitespaceToken)
            _tokens.push_back(token);
    }
    while (token.kind != SyntaxKind::EndOfTileToken);
}

} // end namespace polyglot::CodeAnalysis
