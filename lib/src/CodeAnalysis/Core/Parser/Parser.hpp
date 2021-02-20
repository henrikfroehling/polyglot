#ifndef POLYGLOT_CODEANALYSIS_CORE_PARSER_PARSER_H
#define POLYGLOT_CODEANALYSIS_CORE_PARSER_PARSER_H

#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Parser/Lexer.hpp"

namespace polyglot::CodeAnalysis
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

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_PARSER_PARSER_H
