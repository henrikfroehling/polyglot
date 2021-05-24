#include "Core/Parser/LexerCache.hpp"

namespace polyglot::Core::Parser
{

TokenInfo LexerCache::lookupToken(pg_string_view chars,
                                  unsigned long hashCode,
                                  std::function<TokenInfo(pg_string_view chars)> createTokenInfoFunction) noexcept
{
    TokenInfo tokenInfo = _tokenCache.lookupItem(chars, hashCode);

    if (tokenInfo == TokenInfo{})
    {
        tokenInfo = createTokenInfoFunction(chars);
        _tokenCache.addItem(chars, hashCode, tokenInfo);
    }

    return tokenInfo;
}

} // end namespace polyglot::Core::Parser
