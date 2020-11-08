#ifndef POLYGLOT_CODEANALYSIS_CORE_PARSER_H
#define POLYGLOT_CODEANALYSIS_CORE_PARSER_H

#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/Lexer.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/Core/Types.hpp"

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
    SyntaxNodePtr parse() noexcept;

protected:
    explicit Parser(std::shared_ptr<Lexer> lexer) noexcept;
    virtual SyntaxNodePtr parseRoot() noexcept = 0;
    inline const SyntaxTokenPtr& currentToken() noexcept { return _ptrLexer->currentToken(); }
    inline SyntaxTokenPtr takeToken(SyntaxKind syntaxKind) noexcept { return _ptrLexer->takeToken(syntaxKind); }
    inline SyntaxTokenPtr takeToken() noexcept { return _ptrLexer->takeToken(); }
    inline SyntaxTokenPtr takeContextualToken(SyntaxKind syntaxKind) noexcept { return _ptrLexer->takeContextualToken(syntaxKind); }
    inline const SyntaxTokenPtr& peekToken(pg_size n) noexcept { return _ptrLexer->peekToken(n); }
    inline void advance() noexcept { _ptrLexer->advance(); }

protected:
    std::shared_ptr<Lexer> _ptrLexer;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_PARSER_H
