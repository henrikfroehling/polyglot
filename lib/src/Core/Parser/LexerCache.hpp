#ifndef POLYGLOT_CORE_PARSER_LEXERCACHE_H
#define POLYGLOT_CORE_PARSER_LEXERCACHE_H

#include <functional>
#include "polyglot/Core/Types.hpp"
#include "Core/Parser/TextKeyedCache.hpp"
#include "Core/Parser/TokenInfo.hpp"

namespace polyglot::Core::Parser
{

class LexerCache
{
public:
    static constexpr pg_size MAX_CACHED_TOKEN_SIZE = 50;

public:
    TokenInfo lookupToken(pg_string_view chars,
                          unsigned long hashCode,
                          std::function<TokenInfo(pg_string_view chars)> createTokenInfoFunction) noexcept;

    TokenInfo lookupTrivia(pg_string_view chars,
                           unsigned long hashCode,
                           std::function<TokenInfo()> createTokenInfoFunction) noexcept;

private:
    TextKeyedCache _tokenCache{};
    TextKeyedCache _triviaCache{};
};

} // end namespace polyglot::Core::Parser

#endif // POLYGLOT_CORE_PARSER_LEXERCACHE_H
