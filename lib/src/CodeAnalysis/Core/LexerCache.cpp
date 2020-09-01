#include "polyglot/CodeAnalysis/Core/LexerCache.hpp"
#include "polyglot/CodeAnalysis/Core/Lexer.hpp"

namespace polyglot::CodeAnalysis
{

pg_size LexerCache::CACHE_HITS = 0;
pg_size LexerCache::CACHE_MISSES = 0;

LexerCache::LexerCache(Lexer* lexer) noexcept
    : _tokenCacheN{},
      _triviaCacheN{},
      _pLexer{lexer}
{}

TokenInfo LexerCache::lookupToken(std::string_view chars,
                                  int hashCode,
                                  std::function<TokenInfo(std::string_view chars)> createTokenInfoFunction) noexcept
{
    TokenInfo tokenInfo = _tokenCacheN.lookupItem(chars, hashCode);

    if (tokenInfo == TokenInfo{})
    {
        tokenInfo = createTokenInfoFunction(chars);
        _tokenCacheN.addItem(chars, hashCode, tokenInfo);
        CACHE_MISSES++;
    }
    else
        CACHE_HITS++;

    return tokenInfo;
}

TokenInfo LexerCache::lookupTrivia(std::string_view chars,
                                   int hashCode,
                                   std::function<TokenInfo()> createTokenInfoFunction) noexcept
{
    TokenInfo tokenInfo = _triviaCacheN.lookupItem(chars, hashCode);

    if (tokenInfo == TokenInfo{})
    {
        tokenInfo = createTokenInfoFunction();
        _triviaCacheN.addItem(chars, hashCode, tokenInfo);
        CACHE_MISSES++;
    }
    else
        CACHE_HITS++;

    return tokenInfo;
}

} // end namespace polyglot::CodeAnalysis
