#ifndef POLYGLOT_CODEANALYSIS_CORE_PARSER_PARSER_H
#define POLYGLOT_CODEANALYSIS_CORE_PARSER_PARSER_H

#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Parser/Lexer.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxNode;
class LanguageSyntaxToken;

class Parser
{
public:
    Parser() = delete;
    virtual ~Parser() noexcept;
    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;
    Parser(Parser&&) = delete;
    Parser& operator=(Parser&&) = delete;
    LanguageSyntaxNode* parse() noexcept;

protected:
    explicit Parser(std::shared_ptr<Lexer> lexer) noexcept;
    virtual LanguageSyntaxNode* parseRoot() noexcept = 0;
    inline LanguageSyntaxToken* currentToken() noexcept { return _ptrLexer->currentToken(); }
    inline LanguageSyntaxToken* takeToken(SyntaxKind syntaxKind) noexcept { return _ptrLexer->takeToken(syntaxKind); }
    inline LanguageSyntaxToken* takeToken() noexcept { return _ptrLexer->takeToken(); }
    inline LanguageSyntaxToken* peekToken(pg_size n) noexcept { return _ptrLexer->peekToken(n); }
    inline void advance() noexcept { _ptrLexer->advance(); }

protected:
    SharedPtr<Lexer> _ptrLexer;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_PARSER_PARSER_H
