#ifndef POLYGLOT_CODEANALYSIS_CORE_LEXER_H
#define POLYGLOT_CODEANALYSIS_CORE_LEXER_H

#include <limits>
#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/DirectiveStack.hpp"
#include "polyglot/CodeAnalysis/Core/LexerCache.hpp"
#include "polyglot/CodeAnalysis/Core/TokenInfo.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Nodes/SyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/Tokens/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SlidingTextWindow.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SourceText.hpp"

namespace polyglot::CodeAnalysis
{

enum class LexerMode
{
    Syntax,
    Directive
};

class POLYGLOT_API Lexer : public std::enable_shared_from_this<Lexer>
{
public:
    static constexpr char INVALID_CHARACTER = std::numeric_limits<char>::max();

public:
    virtual ~Lexer();
    Lexer(const Lexer&) = delete;
    Lexer& operator=(const Lexer&) = delete;
    Lexer(Lexer&&) = delete;
    Lexer& operator=(Lexer&&) = delete;
    inline SyntaxTokenPtr lex() noexcept { return lex(_mode); }
    inline const SlidingTextWindow& textWindow() const noexcept { return _textWindow; }
    void preLex() noexcept;
    const SyntaxTokenPtr& currentToken() noexcept;
    SyntaxTokenPtr takeToken(SyntaxKind syntaxKind) noexcept;
    SyntaxTokenPtr takeToken() noexcept;
    SyntaxTokenPtr takeContextualToken(SyntaxKind syntaxKind) noexcept;
    const SyntaxTokenPtr& peekToken(pg_size n) noexcept;
    void advance() noexcept;
    inline void setMode(LexerMode mode) noexcept { _mode = mode; }

protected:
    explicit Lexer(SourceTextPtr sourceText) noexcept;
    void start() noexcept;
    virtual SyntaxTokenPtr lex(LexerMode mode) noexcept = 0;
    void addLexedToken(SyntaxTokenPtr token) noexcept;

protected:
    SlidingTextWindow _textWindow;
    LexerMode _mode;
    LexerCache _lexerCache;
    std::vector<SyntaxNodePtr> _leadingTrivia;
    std::vector<SyntaxNodePtr> _trailingTrivia;
    std::vector<SyntaxTokenPtr> _lexedTokens;
    pg_size _tokenCount;
    pg_size _tokenOffset;
    SyntaxTokenPtr _ptrCurrentToken;
    DirectiveStack _directives;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_LEXER_H
