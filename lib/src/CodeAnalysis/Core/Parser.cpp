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
    SyntaxKind tokenKind = SyntaxKind::EndOfTileToken;

    do
    {
        token = _ptrLexer->nextToken();
        tokenKind = token.syntaxKind();

        if (tokenKind != SyntaxKind::WhitespaceToken)
            _tokens.push_back(token);
    }
    while (tokenKind != SyntaxKind::EndOfTileToken);
}

} // end namespace polyglot::CodeAnalysis
