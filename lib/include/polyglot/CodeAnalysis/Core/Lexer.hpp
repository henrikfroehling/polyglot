#ifndef POLYGLOT_CODEANALYSIS_CORE_LEXER_H
#define POLYGLOT_CODEANALYSIS_CORE_LEXER_H

#include <limits>
#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/LexerCache.hpp"
#include "polyglot/CodeAnalysis/Core/TokenInfo.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SlidingTextWindow.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SourceText.hpp"

namespace polyglot::CodeAnalysis
{

enum class LexerMode
{
    Syntax,
    Directive
};

class POLYGLOT_API Lexer
{
public:
    static constexpr char INVALID_CHARACTER = std::numeric_limits<char>::max();

public:
    virtual ~Lexer();
    Lexer(const Lexer&) = delete;
    Lexer& operator=(const Lexer&) = delete;
    Lexer(Lexer&&) = delete;
    Lexer& operator=(Lexer&&) = delete;
    virtual SyntaxTokenPtr nextToken() noexcept = 0;
    inline const SlidingTextWindow& textWindow() const noexcept { return _textWindow; }

protected:
    explicit Lexer(SourceTextPtr sourceText) noexcept;
    void start() noexcept;
    virtual TokenInfo quickScanSyntaxToken() noexcept { return TokenInfo{}; }

protected:
    SlidingTextWindow _textWindow;
    LexerMode _mode;
    LexerCache _lexerCache;
    std::vector<SyntaxTriviaPtr> _leadingTrivia;
    std::vector<SyntaxTriviaPtr> _trailingTrivia;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_LEXER_H
