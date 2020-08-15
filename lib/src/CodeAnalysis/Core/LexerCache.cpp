#include "polyglot/CodeAnalysis/Core/LexerCache.hpp"
#include "polyglot/CodeAnalysis/Core/Lexer.hpp"

#ifdef COLLECT_BENCHMARKS
#include "polyglot/CodeAnalysis/Core/LexerBenchmark.hpp"
#endif

namespace polyglot::CodeAnalysis
{

LexerCache::LexerCache(Lexer* lexer) noexcept
    : _triviaCache{},
      _tokenCache{},
      _pLexer{lexer}
{}

SyntaxTokenPtr LexerCache::lookupToken(std::string_view chars,
                                       int hashCode,
                                       std::function<SyntaxTokenPtr(std::string_view chars)> createTokenFunction) noexcept
{
    auto ptrSyntaxToken = _tokenCache.lookupItem(chars, hashCode);

    if (ptrSyntaxToken == nullptr)
    {
#ifdef COLLECT_BENCHMARKS
        _pLexer->benchmark().incrementCacheMisses();
#endif
        ptrSyntaxToken = createTokenFunction(chars);
        _tokenCache.addItem(chars, hashCode, ptrSyntaxToken);
    }
#ifdef COLLECT_BENCHMARKS
    else
        _pLexer->benchmark().incrementCacheHits();
#endif

    return ptrSyntaxToken;
}

SyntaxTriviaPtr LexerCache::lookupTrivia(std::string_view chars,
                                         int hashCode,
                                         std::function<SyntaxTriviaPtr()> createTriviaFunction) noexcept
{
    auto ptrSyntaxTrivia = _triviaCache.lookupItem(chars, hashCode);

    if (ptrSyntaxTrivia == nullptr)
    {
#ifdef COLLECT_BENCHMARKS
        _pLexer->benchmark().incrementCacheMisses();
#endif
        ptrSyntaxTrivia = createTriviaFunction();
        _triviaCache.addItem(chars, hashCode, ptrSyntaxTrivia);
    }
#ifdef COLLECT_BENCHMARKS
    else
        _pLexer->benchmark().incrementCacheHits();
#endif

    return ptrSyntaxTrivia;
}

} // end namespace polyglot::CodeAnalysis
