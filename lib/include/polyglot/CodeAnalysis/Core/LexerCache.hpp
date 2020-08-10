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

class Lexer;

class POLYGLOT_API LexerCache
{
public:
    static constexpr pg_size MAX_CACHED_TOKEN_SIZE = 50;

public:
    explicit LexerCache(Lexer* lexer) noexcept;

    std::shared_ptr<SyntaxToken> lookupToken(std::string_view chars,
                                             int hashCode,
                                             std::function<std::shared_ptr<SyntaxToken>(std::string_view chars)> createTokenFunction) noexcept;

    std::shared_ptr<SyntaxTrivia> lookupTrivia(std::string_view chars,
                                               int hashCode,
                                               std::function<std::shared_ptr<SyntaxTrivia>()> createTriviaFunction) noexcept;

private:
    TextKeyedCache<SyntaxTrivia> _triviaCache;
    TextKeyedCache<SyntaxToken> _tokenCache;
    Lexer* _pLexer;
};

} // end namespace polyglot::CodeAnalyis

#endif // POLYGLOT_CODEANALYSIS_CORE_LEXERCACHE_H
