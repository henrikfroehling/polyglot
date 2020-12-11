#include "polyglot/CodeAnalysis/Core/Lexer.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Core/Syntax/SyntaxToken.hpp"
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
        SyntaxToken* ptrToken = lex();
        assert(ptrToken != nullptr);
        _lexedTokens.push_back(ptrToken);
        _tokenCount++;
        _tokenOffset++;

        if (ptrToken->syntaxKind() == SyntaxKind::EndOfFileToken)
            break;
    }

    _tokenOffset = currentTokenOffset;
}

SyntaxToken* Lexer::currentToken() noexcept
{
    if (_tokenOffset >= _tokenCount)
        addLexedToken(lex());

    return _lexedTokens[_tokenOffset];
}

SyntaxToken* Lexer::takeToken(SyntaxKind syntaxKind) noexcept
{
    _ptrCurrentToken = currentToken();

    if (_ptrCurrentToken->syntaxKind() == syntaxKind)
    {
        _tokenOffset++;
        return _ptrCurrentToken;
    }

    // TODO Create missing replacement token
    return nullptr;
}

SyntaxToken* Lexer::takeToken() noexcept
{
    _ptrCurrentToken = currentToken();
    _tokenOffset++;
    return _ptrCurrentToken;
}

SyntaxToken* Lexer::peekToken(pg_size n) noexcept
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

void Lexer::addLexedToken(SyntaxToken* token) noexcept
{
    assert(token != nullptr);

    if (_tokenCount == _lexedTokens.size())
        _lexedTokens.resize(_tokenCount + 2);

    _lexedTokens[_tokenCount] = token;
    _tokenCount++;
}

} // end namespace polyglot::CodeAnalysis
