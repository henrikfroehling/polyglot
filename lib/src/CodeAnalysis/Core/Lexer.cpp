#include "polyglot/CodeAnalysis/Core/Lexer.hpp"
#include <cassert>
#include <algorithm>

namespace polyglot::CodeAnalysis
{

constexpr pg_size MIN_LEXED_TOKENS_COUNT{32};
constexpr pg_size MAX_LEXED_TOKENS_COUNT{4096};

Lexer::Lexer(SharedPtr<SourceText> sourceText) noexcept
    : _textWindow{std::move(sourceText)},
      _mode{LexerMode::Syntax},
      _lexerCache{this},
      _leadingTrivia{},
      _trailingTrivia{},
      _lexedTokens{},
      _tokenCount{},
      _tokenOffset{},
      _ptrCurrentToken{nullptr},
      _directives{}
{}

Lexer::~Lexer()
{}

void Lexer::start() noexcept
{
    _textWindow.start();
}

void Lexer::preLex() noexcept
{
    const pg_size currentTokenOffset = _tokenOffset;
    _lexedTokens.clear();
    _tokenOffset = _tokenCount;

    const pg_size size = std::min(static_cast<pg_size>(MAX_LEXED_TOKENS_COUNT),
                                  std::max(static_cast<pg_size>(MIN_LEXED_TOKENS_COUNT),
                                           textWindow().content().length() / 2));

    _lexedTokens.reserve(size);

    for (pg_size i = 0; i < size; i++)
    {
        SharedPtr<SyntaxToken> ptrToken = lex();
        assert(ptrToken != nullptr);
        _lexedTokens.push_back(ptrToken);
        _tokenCount++;
        _tokenOffset++;

        if (ptrToken->syntaxKind() == SyntaxKind::EndOfFileToken)
            break;
    }

    _tokenOffset = currentTokenOffset;
}

const SharedPtr<SyntaxToken>& Lexer::currentToken() noexcept
{
    if (_tokenOffset >= _tokenCount)
        addLexedToken(lex());

    return _lexedTokens[_tokenOffset];
}

SharedPtr<SyntaxToken> Lexer::takeToken(SyntaxKind syntaxKind) noexcept
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

SharedPtr<SyntaxToken> Lexer::takeToken() noexcept
{
    auto& ptrCurrentToken = currentToken();
    _tokenOffset++;
    return ptrCurrentToken;
}

SharedPtr<SyntaxToken> Lexer::takeContextualToken(SyntaxKind syntaxKind) noexcept
{
    auto& ptrCurrentToken = currentToken();

    if (ptrCurrentToken->contextualKind() == syntaxKind)
    {
        _tokenOffset++;
        return ptrCurrentToken;
    }

    // TODO create missing replacement token / error handling
    return nullptr;
}

const SharedPtr<SyntaxToken>& Lexer::peekToken(pg_size n) noexcept
{
    assert(n >= 0);

    while (_tokenOffset + n >= _tokenCount)
        addLexedToken(lex());

    return _lexedTokens[_tokenOffset + n];
}

void Lexer::advance() noexcept
{
    _tokenOffset++;
}

void Lexer::addLexedToken(SharedPtr<SyntaxToken> token) noexcept
{
    assert(token != nullptr);
    pg_size newSize{2};

    if (_lexedTokens.size() > 0)
        newSize = _lexedTokens.size() * 2;

    _lexedTokens.resize(newSize);
    _lexedTokens[_tokenCount] = token;
    _tokenCount++;
}

} // end namespace polyglot::CodeAnalysis
