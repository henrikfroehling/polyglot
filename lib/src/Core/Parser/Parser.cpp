#include "Parser.hpp"

namespace polyglot::Core::Parser
{

Parser::Parser(std::shared_ptr<Lexer> lexer) noexcept
    : _ptrLexer{std::move(lexer)}
{}

Parser::~Parser() noexcept
{}

ISyntaxNode* Parser::parse() noexcept
{
    _ptrLexer->preLex();
    return parseRoot();
}

} // end namespace polyglot::Core::Parser
