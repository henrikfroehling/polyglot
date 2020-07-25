#include "polyglot/CodeAnalysis/Core/LexerCache.hpp"

namespace polyglot::CodeAnalysis
{

std::shared_ptr<SyntaxToken> LexerCache::lookupToken(std::string_view chars,
                                                     int hashCode,
                                                     std::function<std::shared_ptr<SyntaxToken>()> createTokenFunction) noexcept
{
    auto ptrSyntaxToken = _tokenCache.lookupItem(chars, hashCode);

    if (ptrSyntaxToken == nullptr)
    {
#ifndef NDEBUG
        CacheMiss();
#endif
        ptrSyntaxToken = createTokenFunction();
        _tokenCache.addItem(chars, hashCode, ptrSyntaxToken);
    }
#ifndef NDEBUG
    else
    {
        CacheHit();
    }
#endif

    return ptrSyntaxToken;
}

} // end namespace polyglot::CodeAnalysis
