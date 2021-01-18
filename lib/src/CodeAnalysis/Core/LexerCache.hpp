#ifndef POLYGLOT_CODEANALYSIS_CORE_LEXERCACHE_H
#define POLYGLOT_CODEANALYSIS_CORE_LEXERCACHE_H

#include <functional>
#include <string_view>
#include "CodeAnalysis/Core/TextKeyedCache.hpp"
#include "CodeAnalysis/Core/TokenInfo.hpp"

namespace polyglot::CodeAnalysis
{

class LexerCache
{
public:
    static constexpr pg_size MAX_CACHED_TOKEN_SIZE = 50;

public:
    TokenInfo lookupToken(std::string_view chars,
                          int hashCode,
                          std::function<TokenInfo(std::string_view chars)> createTokenInfoFunction) noexcept;

    TokenInfo lookupTrivia(std::string_view chars,
                           int hashCode,
                           std::function<TokenInfo()> createTokenInfoFunction) noexcept;

private:
    TextKeyedCache _tokenCache{};
    TextKeyedCache _triviaCache{};
};

} // end namespace polyglot::CodeAnalyis

#endif // POLYGLOT_CODEANALYSIS_CORE_LEXERCACHE_H
