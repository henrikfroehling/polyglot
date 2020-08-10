#ifndef POLYGLOT_CODEANALYSIS_CORE_LEXER_H
#define POLYGLOT_CODEANALYSIS_CORE_LEXER_H

#include <limits>
#include <memory>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/LexerCache.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Text/SlidingTextWindow.hpp"

namespace polyglot::CodeAnalysis
{

class SourceText;

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
    virtual std::shared_ptr<SyntaxToken> nextToken() noexcept = 0;

#ifndef NDEBUG
    inline int cacheMisses() const noexcept { return _lexerCache.cacheMisses(); }
    inline int cacheHits() const noexcept { return _lexerCache.cacheHits(); }
#endif

protected:
    explicit Lexer(SourceText* sourceText) noexcept;
    void start() noexcept;
    virtual std::shared_ptr<SyntaxToken> quickScanSyntaxToken() noexcept { return nullptr; }

protected:
    SlidingTextWindow _textWindow;
    LexerCache _lexerCache;
    std::vector<std::shared_ptr<SyntaxTrivia>> _leadingTrivia;
    std::vector<std::shared_ptr<SyntaxTrivia>> _trailingTrivia;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_LEXER_H
