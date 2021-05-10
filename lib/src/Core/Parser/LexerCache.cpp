#include "Core/Parser/LexerCache.hpp"

namespace polyglot::Core::Parser
{

TokenInfo LexerCache::lookupToken(std::string_view chars,
                                  int hashCode,
                                  std::function<TokenInfo(std::string_view chars)> createTokenInfoFunction) noexcept
{
    TokenInfo tokenInfo = _tokenCache.lookupItem(chars, hashCode);

    if (tokenInfo == TokenInfo{})
    {
        tokenInfo = createTokenInfoFunction(chars);
        _tokenCache.addItem(chars, hashCode, tokenInfo);
    }

    return tokenInfo;
}

TokenInfo LexerCache::lookupTrivia(std::string_view chars,
                                   int hashCode,
                                   std::function<TokenInfo()> createTokenInfoFunction) noexcept
{
    TokenInfo tokenInfo = _triviaCache.lookupItem(chars, hashCode);

    if (tokenInfo == TokenInfo{})
    {
        tokenInfo = createTokenInfoFunction();
        _triviaCache.addItem(chars, hashCode, tokenInfo);
    }

    return tokenInfo;
}

} // end namespace polyglot::Core::Parser
