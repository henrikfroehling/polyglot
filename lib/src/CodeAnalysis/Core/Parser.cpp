#include "polyglot/CodeAnalysis/Core/Parser.hpp"

#ifdef COLLECT_BENCHMARKS
#include "polyglot/CodeAnalysis/Core/LexerBenchmark.hpp"
#endif

#include <cassert>
#include <algorithm>

namespace polyglot::CodeAnalysis
{

Parser::Parser(std::unique_ptr<Lexer> lexer) noexcept
    : _ptrLexer{std::move(lexer)},
      _lexedTokens{},
      _tokenCount{},
      _tokenOffset{},
      _ptrCurrentToken{nullptr}
{}

Parser::~Parser() noexcept
{}

SyntaxNodePtr Parser::parse() noexcept
{
    preLex();
    return parseRoot();
}

void Parser::preLex() noexcept
{
    _lexedTokens.clear();

    const pg_size size = std::min(static_cast<pg_size>(4096),
                                  std::max(static_cast<pg_size>(32), _ptrLexer->textWindow().text().length()));

    _lexedTokens.reserve(size);

    for (pg_size i = 0; i < size; i++)
    {
        SyntaxTokenPtr ptrToken = _ptrLexer->nextToken();
        assert(ptrToken != nullptr);
        _lexedTokens.push_back(ptrToken);
        _tokenCount++;

        if (ptrToken->syntaxKind() == SyntaxKind::EndOfFileToken)
            break;
    }
}

const SyntaxTokenPtr& Parser::currentToken() noexcept
{
    if (_tokenOffset >= _tokenCount)
        addLexedToken(_ptrLexer->nextToken());

    return _lexedTokens[_tokenOffset];
}

SyntaxTokenPtr Parser::takeToken(SyntaxKind syntaxKind) noexcept
{
    auto& ptrCurrentToken = currentToken();

    if (ptrCurrentToken->syntaxKind() == syntaxKind)
    {
        _tokenOffset++;
        return ptrCurrentToken;
    }

    // TODO Create missing replacement token
    return nullptr;
}

SyntaxTokenPtr Parser::takeToken() noexcept
{
    auto& ptrCurrentToken = currentToken();
    _tokenOffset++;
    return ptrCurrentToken;
}

const SyntaxTokenPtr& Parser::peekToken(pg_size n) noexcept
{
    assert(n >= 0);

    while (_tokenOffset + n >= _tokenCount)
        addLexedToken(_ptrLexer->nextToken());

    return _lexedTokens[_tokenOffset + n];
}

void Parser::advance() noexcept
{
    _tokenOffset++;
}

void Parser::addLexedToken(SyntaxTokenPtr token) noexcept
{
    assert(token != nullptr);

    if (_tokenCount >= _lexedTokens.size())
        _lexedTokens.resize(_lexedTokens.size() * 2);

    _lexedTokens[_tokenCount] = token;
    _tokenCount++;
}

} // end namespace polyglot::CodeAnalysis
