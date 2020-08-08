#ifndef POLYGLOT_CODEANALYSIS_CORE_LEXERCACHE_H
#define POLYGLOT_CODEANALYSIS_CORE_LEXERCACHE_H

#include <functional>
#include <memory>
#include <string_view>
#include "polyglot/polyglot_global.hpp"
#include "polyglot/CodeAnalysis/Core/TextKeyedCache.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxTrivia.hpp"

namespace polyglot::CodeAnalysis
{

class POLYGLOT_API LexerCache
{
public:
#ifndef DEBUG
    LexerCache() noexcept
        : _cacheMisses{},
          _cacheHits{}
    {}
#else
    LexerCache() noexcept = default;
#endif

    std::shared_ptr<SyntaxToken> lookupToken(std::string_view chars,
                                             int hashCode,
                                             std::function<std::shared_ptr<SyntaxToken>(std::string_view chars)> createTokenFunction) noexcept;

    std::shared_ptr<SyntaxTrivia> lookupTrivia(std::string_view chars,
                                               int hashCode,
                                               std::function<std::shared_ptr<SyntaxTrivia>()> createTriviaFunction) noexcept;

private:
    TextKeyedCache<SyntaxTrivia> _triviaCache;
    TextKeyedCache<SyntaxToken> _tokenCache;

#ifndef NDEBUG
public:
    inline int cacheMisses() const noexcept { return _cacheMisses; }
    inline int cacheHits() const noexcept { return _cacheHits; }

private:
    inline void CacheMiss() noexcept { _cacheMisses++; }
    inline void CacheHit() noexcept { _cacheHits++; }

private:
    int _cacheMisses;
    int _cacheHits;
#endif
};

} // end namespace polyglot::CodeAnalyis

#endif // POLYGLOT_CODEANALYSIS_CORE_LEXERCACHE_H
