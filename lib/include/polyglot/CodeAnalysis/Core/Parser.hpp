#ifndef POLYGLOT_CODEANALYSIS_CORE_PARSER_H
#define POLYGLOT_CODEANALYSIS_CORE_PARSER_H

#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Lexer.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API Parser
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
    inline SyntaxToken* takeContextualToken(SyntaxKind syntaxKind) noexcept { return _ptrLexer->takeContextualToken(syntaxKind); }
    inline SyntaxToken* peekToken(pg_size n) noexcept { return _ptrLexer->peekToken(n); }
    inline void advance() noexcept { _ptrLexer->advance(); }

protected:
    SharedPtr<Lexer> _ptrLexer;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_PARSER_H
