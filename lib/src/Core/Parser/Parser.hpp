#ifndef POLYGLOT_CORE_PARSER_PARSER_H
#define POLYGLOT_CORE_PARSER_PARSER_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
#include "Lexer.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class ISyntaxToken;
class SyntaxPool;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Core::Parser
{

class Parser
{
public:
    Parser() = delete;
    virtual ~Parser() noexcept {}
    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;
    Parser(Parser&&) = delete;
    Parser& operator=(Parser&&) = delete;
    Syntax::ISyntaxNode* parse() noexcept;
    inline Syntax::SyntaxPool takeSyntaxPool() noexcept { return _ptrLexer->takeSyntaxPool(); }

protected:
    explicit Parser(std::shared_ptr<Lexer> lexer) noexcept;
    virtual Syntax::ISyntaxNode* parseRoot() noexcept = 0;
    inline Syntax::ISyntaxToken* currentToken() noexcept { return _ptrLexer->currentToken(); }
    inline Syntax::ISyntaxToken* takeToken(Syntax::SyntaxKind syntaxKind) noexcept { return _ptrLexer->takeToken(syntaxKind); }
    inline Syntax::ISyntaxToken* takeToken() noexcept { return _ptrLexer->takeToken(); }
    inline Syntax::ISyntaxToken* peekToken(pg_size n) noexcept { return _ptrLexer->peekToken(n); }
    inline void advance() noexcept { _ptrLexer->advance(); }

protected:
    SharedPtr<Lexer> _ptrLexer;
};

} // end namespace polyglot::Core::Parser

#endif // POLYGLOT_CORE_PARSER_PARSER_H
