#include "Core/Parser/Parser.hpp"

namespace polyglot::Core::Parser
{

Parser::Parser(std::shared_ptr<Lexer> lexer) noexcept
    : _ptrLexer{std::move(lexer)}
{}

Syntax::ISyntaxNode* Parser::parse() noexcept
{
    _ptrLexer->preLex();
    return parseRoot();
}

} // end namespace polyglot::Core::Parser
