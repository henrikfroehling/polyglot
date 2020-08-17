#include "polyglot/CodeAnalysis/Core/LexerCache.hpp"
#include "polyglot/CodeAnalysis/Core/Lexer.hpp"

namespace polyglot::CodeAnalysis
{

LexerCache::LexerCache(Lexer* lexer) noexcept
    : _triviaCache{},
      _tokenCache{},
      _pLexer{lexer}
{}

SyntaxTokenPtr LexerCache::lookupToken(std::string_view chars,
                                       int hashCode,
                                       std::function<SyntaxTokenPtr(std::string_view chars)> createTokenFunction) noexcept
{
    auto ptrSyntaxToken = _tokenCache.lookupItem(chars, hashCode);

    if (ptrSyntaxToken == nullptr)
    {
        ptrSyntaxToken = createTokenFunction(chars);
        _tokenCache.addItem(chars, hashCode, ptrSyntaxToken);
    }

    return ptrSyntaxToken;
}

SyntaxTriviaPtr LexerCache::lookupTrivia(std::string_view chars,
                                         int hashCode,
                                         std::function<SyntaxTriviaPtr()> createTriviaFunction) noexcept
{
    auto ptrSyntaxTrivia = _triviaCache.lookupItem(chars, hashCode);

    if (ptrSyntaxTrivia == nullptr)
    {
        ptrSyntaxTrivia = createTriviaFunction();
        _triviaCache.addItem(chars, hashCode, ptrSyntaxTrivia);
    }

    return ptrSyntaxTrivia;
}

} // end namespace polyglot::CodeAnalysis
