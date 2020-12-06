#include "polyglot/CodeAnalysis/Core/Parser.hpp"

namespace polyglot::CodeAnalysis
{

Parser::Parser(std::shared_ptr<Lexer> lexer) noexcept
    : _ptrLexer{ std::move(lexer) }
{}

Parser::~Parser() noexcept
{}

Ptr<SyntaxNode> Parser::parse() noexcept
{
    _ptrLexer->preLex();
    return parseRoot();
}

} // end namespace polyglot::CodeAnalysis
