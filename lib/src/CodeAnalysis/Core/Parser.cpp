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
    SyntaxKind tokenKind = SyntaxKind::EndOfFileToken;

    do
    {
        auto ptrToken = _ptrLexer->nextToken();
        tokenKind = ptrToken->syntaxKind();

        if (tokenKind != SyntaxKind::WhitespaceToken)
            _tokens.push_back(std::move(ptrToken));
    }
    while (tokenKind != SyntaxKind::EndOfFileToken);
}

} // end namespace polyglot::CodeAnalysis
