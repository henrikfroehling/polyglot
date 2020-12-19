#ifndef POLYGLOT_CODEANALYSIS_CORE_LEXER_H
#define POLYGLOT_CODEANALYSIS_CORE_LEXER_H

#include <limits>
#include <memory>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/Text/TextWindow.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SourceText.hpp"
#include "CodeAnalysis/Core/DirectiveStack.hpp"
#include "CodeAnalysis/Core/LexerCache.hpp"
#include "CodeAnalysis/Core/LexerMode.hpp"
#include "CodeAnalysis/Core/TokenInfo.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxNode;
class SyntaxToken;

class Lexer : public std::enable_shared_from_this<Lexer>
{
public:
    static constexpr char INVALID_CHARACTER = std::numeric_limits<char>::max();

public:
    virtual ~Lexer();
    Lexer(const Lexer&) = delete;
    Lexer& operator=(const Lexer&) = delete;
    Lexer(Lexer&&) = delete;
    Lexer& operator=(Lexer&&) = delete;
    inline SyntaxToken* lex() noexcept { return lexToken(); }
    inline const TextWindow& textWindow() const noexcept { return _textWindow; }
    void preLex() noexcept;
    SyntaxToken* currentToken() noexcept;
    SyntaxToken* takeToken(SyntaxKind syntaxKind) noexcept;
    SyntaxToken* takeToken() noexcept;
    SyntaxToken* peekToken(pg_size n) noexcept;
    void advance() noexcept;
    void setMode(LexerMode mode) noexcept;

protected:
    explicit Lexer(SharedPtr<SourceText> sourceText) noexcept;
    void start() noexcept;
    virtual SyntaxToken* lexToken() noexcept = 0;
    void addLexedToken(SyntaxToken* token) noexcept;

protected:
    TextWindow _textWindow;
    LexerMode _mode;
    LexerCache _lexerCache;
    std::vector<SyntaxNode*> _leadingTrivia;
    std::vector<SyntaxNode*> _trailingTrivia;
    std::vector<SyntaxToken*> _lexedTokens;
    std::vector<SyntaxToken*> _lexedDirectiveTriviaTokens;
    pg_size _tokenCount;
    pg_size _tokenOffset;
    SyntaxToken* _pCurrentToken;
    DirectiveStack _directives;
    pg_size _directiveTriviaTokenCount;
    pg_size _directiveTriviaTokenOffset;
    SyntaxToken* _pCurrentDirectiveTriviaToken;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_LEXER_H