#ifndef POLYGLOT_CORE_PARSER_LEXER_H
#define POLYGLOT_CORE_PARSER_LEXER_H

#include <limits>
#include <memory>
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Core/Syntax/SyntaxPool.hpp"
#include "Core/Text/SourceText.hpp"
#include "Core/Text/TextWindow.hpp"
#include "DirectiveStack.hpp"
#include "LexerCache.hpp"
#include "LexerMode.hpp"
#include "TokenInfo.hpp"

namespace polyglot::Core::Syntax
{

class ISyntaxNode;
class ISyntaxToken;
class SyntaxPool;

} // end namespace polyglot::Core::Syntax

namespace polyglot::Core::Parser
{

class Lexer : public std::enable_shared_from_this<Lexer>
{
public:
    static constexpr char INVALID_CHARACTER = std::numeric_limits<char>::max();

public:
    virtual ~Lexer() noexcept {}
    Lexer(const Lexer&) = delete;
    Lexer& operator=(const Lexer&) = delete;
    Lexer(Lexer&&) = delete;
    Lexer& operator=(Lexer&&) = delete;
    inline Syntax::ISyntaxToken* lex() noexcept { return lexToken(); }
    inline const Text::TextWindow& textWindow() const noexcept { return _textWindow; }
    void preLex() noexcept;
    Syntax::ISyntaxToken* currentToken() noexcept;
    Syntax::ISyntaxToken* takeToken(Syntax::SyntaxKind syntaxKind) noexcept;
    Syntax::ISyntaxToken* takeToken() noexcept;
    Syntax::ISyntaxToken* peekToken(pg_size n) noexcept;
    void advance() noexcept;
    void setMode(LexerMode mode) noexcept;
    inline Syntax::SyntaxPool& syntaxPool() noexcept { return _syntaxPool; }

    inline Syntax::SyntaxPool takeSyntaxPool() noexcept
    {
        Syntax::SyntaxPool tmp = std::move(_syntaxPool);
        _syntaxPool = Syntax::SyntaxPool{};
        return std::move(tmp);
    }

protected:
    explicit Lexer(SharedPtr<Text::SourceText> sourceText) noexcept;
    void start() noexcept;
    virtual Syntax::ISyntaxToken* lexToken() noexcept = 0;
    void addLexedToken(Syntax::ISyntaxToken* token) noexcept;
    Syntax::ISyntaxToken* createMissingToken(Syntax::SyntaxKind expectedSyntaxKind) noexcept;

protected:
    Text::TextWindow _textWindow;
    LexerMode _mode;
    LexerCache _lexerCache;
    std::vector<Syntax::ISyntaxToken*> _lexedTokens;
    std::vector<Syntax::ISyntaxToken*> _lexedDirectiveTriviaTokens;
    pg_size _tokenCount;
    pg_size _tokenOffset;
    Syntax::ISyntaxToken* _pCurrentToken;
    DirectiveStack _directives;
    pg_size _directiveTriviaTokenCount;
    pg_size _directiveTriviaTokenOffset;
    Syntax::ISyntaxToken* _pCurrentDirectiveTriviaToken;

private:
    Syntax::SyntaxPool _syntaxPool;
    Syntax::SyntaxFactory _syntaxFactory;
};

} // end namespace polyglot::Core::Parser

#endif // POLYGLOT_CORE_PARSER_LEXER_H
