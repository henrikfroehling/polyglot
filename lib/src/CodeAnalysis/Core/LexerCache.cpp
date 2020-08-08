#include "polyglot/CodeAnalysis/Core/LexerCache.hpp"

namespace polyglot::CodeAnalysis
{

std::shared_ptr<SyntaxToken> LexerCache::lookupToken(std::string_view chars,
                                                     int hashCode,
                                                     std::function<std::shared_ptr<SyntaxToken>(std::string_view chars)> createTokenFunction) noexcept
{
    auto ptrSyntaxToken = _tokenCache.lookupItem(chars, hashCode);

    if (ptrSyntaxToken == nullptr)
    {
#ifndef NDEBUG
        CacheMiss();
#endif
        ptrSyntaxToken = createTokenFunction(chars);
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

std::shared_ptr<SyntaxTrivia> LexerCache::lookupTrivia(std::string_view chars,
                                                       int hashCode,
                                                       std::function<std::shared_ptr<SyntaxTrivia>()> createTriviaFunction) noexcept
{
    auto ptrSyntaxTrivia = _triviaCache.lookupItem(chars, hashCode);

    if (ptrSyntaxTrivia == nullptr)
    {
#ifndef NDEBUG
        CacheMiss();
#endif
        ptrSyntaxTrivia = createTriviaFunction();
        _triviaCache.addItem(chars, hashCode, ptrSyntaxTrivia);
    }
#ifndef NDEBUG
    else
    {
        CacheHit();
    }
#endif

    return ptrSyntaxTrivia;
}

} // end namespace polyglot::CodeAnalysis
