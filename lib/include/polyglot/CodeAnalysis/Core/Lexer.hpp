#ifndef POLYGLOT_CODEANALYSIS_CORE_LEXER_H
#define POLYGLOT_CODEANALYSIS_CORE_LEXER_H

#include <limits>
#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/DirectiveStack.hpp"
#include "polyglot/CodeAnalysis/Core/LexerCache.hpp"
#include "polyglot/CodeAnalysis/Core/TokenInfo.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Text/TextWindow.hpp"
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
    inline SharedPtr<SyntaxToken> lex() noexcept { return lex(_mode); }
    inline const TextWindow& textWindow() const noexcept { return _textWindow; }
    void preLex() noexcept;
    const SharedPtr<SyntaxToken>& currentToken() noexcept;
    SharedPtr<SyntaxToken> takeToken(SyntaxKind syntaxKind) noexcept;
    SharedPtr<SyntaxToken> takeToken() noexcept;
    SharedPtr<SyntaxToken> takeContextualToken(SyntaxKind syntaxKind) noexcept;
    const SharedPtr<SyntaxToken>& peekToken(pg_size n) noexcept;
    void advance() noexcept;
    inline void setMode(LexerMode mode) noexcept { _mode = mode; }

protected:
    explicit Lexer(SharedPtr<SourceText> sourceText) noexcept;
    void start() noexcept;
    virtual SharedPtr<SyntaxToken> lex(LexerMode mode) noexcept = 0;
    void addLexedToken(SharedPtr<SyntaxToken> token) noexcept;

protected:
    TextWindow _textWindow;
    LexerMode _mode;
    LexerCache _lexerCache;
    std::vector<SharedPtr<SyntaxNode>> _leadingTrivia;
    std::vector<SharedPtr<SyntaxNode>> _trailingTrivia;
    std::vector<SharedPtr<SyntaxToken>> _lexedTokens;
    pg_size _tokenCount;
    pg_size _tokenOffset;
    SharedPtr<SyntaxToken> _ptrCurrentToken;
    DirectiveStack _directives;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_LEXER_H
