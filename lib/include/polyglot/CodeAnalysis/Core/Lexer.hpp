#ifndef POLYGLOT_CODEANALYSIS_CORE_LEXER_H
#define POLYGLOT_CODEANALYSIS_CORE_LEXER_H

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

protected:
    SlidingTextWindow _textWindow;
    LexerCache _lexerCache;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_LEXER_H
