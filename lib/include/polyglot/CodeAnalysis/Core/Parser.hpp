#ifndef POLYGLOT_CODEANALYSIS_CORE_PARSER_H
#define POLYGLOT_CODEANALYSIS_CORE_PARSER_H

#include <memory>
#include <vector>
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
    explicit Parser(std::unique_ptr<Lexer> lexer) noexcept;
    void preLex() noexcept;
    virtual SyntaxNodePtr parseCore() noexcept = 0;
    SyntaxTokenPtr currentToken() noexcept;
    SyntaxTokenPtr takeToken(SyntaxKind syntaxKind) noexcept;
    SyntaxTokenPtr takeToken() noexcept;
    SyntaxTokenPtr peekToken(pg_size n) noexcept;

protected:
    std::unique_ptr<Lexer> _ptrLexer;
    std::vector<SyntaxTokenPtr> _lexedTokens;
    pg_size _tokenCount;
    pg_size _tokenOffset;
    SyntaxTokenPtr _ptrCurrentToken;

private:
    void addLexedToken(SyntaxTokenPtr token) noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_PARSER_H
