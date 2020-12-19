#ifndef POLYGLOT_CODEANALYSIS_CORE_PARSER_H
#define POLYGLOT_CODEANALYSIS_CORE_PARSER_H

#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Lexer.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxNode;
class SyntaxToken;

class Parser
{
public:
    Parser() = delete;
    virtual ~Parser() noexcept;
    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;
    Parser(Parser&&) = delete;
    Parser& operator=(Parser&&) = delete;
    SyntaxNode* parse() noexcept;

protected:
    explicit Parser(std::shared_ptr<Lexer> lexer) noexcept;
    virtual SyntaxNode* parseRoot() noexcept = 0;
    inline SyntaxToken* currentToken() noexcept { return _ptrLexer->currentToken(); }
    inline SyntaxToken* takeToken(SyntaxKind syntaxKind) noexcept { return _ptrLexer->takeToken(syntaxKind); }
    inline SyntaxToken* takeToken() noexcept { return _ptrLexer->takeToken(); }
    inline SyntaxToken* peekToken(pg_size n) noexcept { return _ptrLexer->peekToken(n); }
    inline void advance() noexcept { _ptrLexer->advance(); }

protected:
    SharedPtr<Lexer> _ptrLexer;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_PARSER_H
