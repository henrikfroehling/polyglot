#ifndef POLYGLOT_CORE_PARSER_PARSER_H
#define POLYGLOT_CORE_PARSER_PARSER_H

#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Types.hpp"
#include "Lexer.hpp"

namespace polyglot::Core::Parser
{

class ISyntaxNode;
class ISyntaxToken;
class SyntaxPool;

class Parser
{
public:
    Parser() = delete;
    virtual ~Parser() noexcept;
    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;
    Parser(Parser&&) = delete;
    Parser& operator=(Parser&&) = delete;
    ISyntaxNode* parse() noexcept;
    inline SyntaxPool takeSyntaxPool() noexcept { return _ptrLexer->takeSyntaxPool(); }

protected:
    explicit Parser(std::shared_ptr<Lexer> lexer) noexcept;
    virtual ISyntaxNode* parseRoot() noexcept = 0;
    inline ISyntaxToken* currentToken() noexcept { return _ptrLexer->currentToken(); }
    inline ISyntaxToken* takeToken(SyntaxKind syntaxKind) noexcept { return _ptrLexer->takeToken(syntaxKind); }
    inline ISyntaxToken* takeToken() noexcept { return _ptrLexer->takeToken(); }
    inline ISyntaxToken* peekToken(pg_size n) noexcept { return _ptrLexer->peekToken(n); }
    inline void advance() noexcept { _ptrLexer->advance(); }

protected:
    SharedPtr<Lexer> _ptrLexer;
};

} // end namespace polyglot::Core::Parser

#endif // POLYGLOT_CORE_PARSER_PARSER_H
