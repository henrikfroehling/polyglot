#ifndef POLYGLOT_CODEANALYSIS_CORE_LEXERCACHE_H
#define POLYGLOT_CODEANALYSIS_CORE_LEXERCACHE_H

#include <functional>
#include <memory>
#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/TextKeyedCache.hpp"
#include "polyglot/CodeAnalysis/Core/TokenInfo.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"

namespace polyglot::CodeAnalysis
{

class Lexer;

class POLYGLOT_API LexerCache
{
public:
    static constexpr pg_size MAX_CACHED_TOKEN_SIZE = 50;

    static pg_size CACHE_HITS;
    static pg_size CACHE_MISSES;

public:
    explicit LexerCache(Lexer* lexer) noexcept;

    TokenInfo lookupToken(std::string_view chars,
                          int hashCode,
                          std::function<TokenInfo(std::string_view chars)> createTokenInfoFunction) noexcept;

    TokenInfo lookupTrivia(std::string_view chars,
                           int hashCode,
                           std::function<TokenInfo()> createTokenInfoFunction) noexcept;

private:
    TextKeyedCache _tokenCacheN;
    TextKeyedCache _triviaCacheN;
    Lexer* _pLexer;
};

} // end namespace polyglot::CodeAnalyis

#endif // POLYGLOT_CODEANALYSIS_CORE_LEXERCACHE_H
