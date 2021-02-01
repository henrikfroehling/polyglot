#ifndef POLYGLOT_CODEANALYSIS_CORE_PARSER_LEXER_H
#define POLYGLOT_CODEANALYSIS_CORE_PARSER_LEXER_H

#include <limits>
#include <memory>
#include "polyglot/Core/Types.hpp"
#include "CodeAnalysis/Core/Parser/DirectiveStack.hpp"
#include "CodeAnalysis/Core/Parser/LexerCache.hpp"
#include "CodeAnalysis/Core/Parser/LexerMode.hpp"
#include "CodeAnalysis/Core/Parser/TokenInfo.hpp"
#include "CodeAnalysis/Core/Text/TextWindow.hpp"
#include "CodeAnalysis/Core/Text/SourceText.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxNode;
class LanguageSyntaxToken;
class SyntaxPool;

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
    inline LanguageSyntaxToken* lex() noexcept { return lexToken(); }
    inline const TextWindow& textWindow() const noexcept { return _textWindow; }
    void preLex() noexcept;
    LanguageSyntaxToken* currentToken() noexcept;
    LanguageSyntaxToken* takeToken(SyntaxKind syntaxKind) noexcept;
    LanguageSyntaxToken* takeToken() noexcept;
    LanguageSyntaxToken* peekToken(pg_size n) noexcept;
    void advance() noexcept;
    void setMode(LexerMode mode) noexcept;
    inline SyntaxPool& syntaxPool() const noexcept { return _syntaxPool; }

protected:
    explicit Lexer(SharedPtr<SourceText> sourceText,
                   SyntaxPool& syntaxPool) noexcept;

    void start() noexcept;
    virtual LanguageSyntaxToken* lexToken() noexcept = 0;
    void addLexedToken(LanguageSyntaxToken* token) noexcept;
    LanguageSyntaxToken* createMissingToken(SyntaxKind expectedSyntaxKind) noexcept;

protected:
    TextWindow _textWindow;
    LexerMode _mode;
    LexerCache _lexerCache;
    std::vector<LanguageSyntaxToken*> _lexedTokens;
    std::vector<LanguageSyntaxToken*> _lexedDirectiveTriviaTokens;
    pg_size _tokenCount;
    pg_size _tokenOffset;
    LanguageSyntaxToken* _pCurrentToken;
    DirectiveStack _directives;
    pg_size _directiveTriviaTokenCount;
    pg_size _directiveTriviaTokenOffset;
    LanguageSyntaxToken* _pCurrentDirectiveTriviaToken;
    SyntaxPool& _syntaxPool;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_PARSER_LEXER_H
