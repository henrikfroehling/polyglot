#include "CodeAnalysis/Core/Parser.hpp"

namespace polyglot::CodeAnalysis
{

Parser::Parser(std::shared_ptr<Lexer> lexer) noexcept
    : _ptrLexer{std::move(lexer)}
{}

Parser::~Parser() noexcept
{}

LanguageSyntaxNode* Parser::parse() noexcept
{
    _ptrLexer->preLex();
    return parseRoot();
}

} // end namespace polyglot::CodeAnalysis
