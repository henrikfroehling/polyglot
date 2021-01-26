#include "CodeAnalysis/Core/Lexer.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxNode.hpp"
#include "CodeAnalysis/Core/Syntax/LanguageSyntaxToken.hpp"
#include <cassert>
#include <algorithm>

namespace polyglot::CodeAnalysis
{

constexpr pg_size MIN_LEXED_TOKENS_COUNT{32};
constexpr pg_size MAX_LEXED_TOKENS_COUNT{4096};

Lexer::Lexer(SharedPtr<SourceText> sourceText,
             SyntaxPool& syntaxPool) noexcept
    : _textWindow{std::move(sourceText)},
      _mode{LexerMode::Syntax},
      _lexerCache{},
      _lexedTokens{},
      _lexedDirectiveTriviaTokens{},
      _tokenCount{},
      _tokenOffset{},
      _pCurrentToken{nullptr},
      _directives{},
      _directiveTriviaTokenCount{},
      _directiveTriviaTokenOffset{},
      _pCurrentDirectiveTriviaToken{nullptr},
      _syntaxPool{syntaxPool}
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
    _tokenOffset = _tokenCount;

    const pg_size size = std::min(static_cast<pg_size>(MAX_LEXED_TOKENS_COUNT),
                                  std::max(static_cast<pg_size>(MIN_LEXED_TOKENS_COUNT),
                                           _textWindow.content().length() / 2));

    _lexedTokens.reserve(size);

    for (pg_size i = 0; i < size; i++)
    {
        LanguageSyntaxToken* pToken = lex();
        addLexedToken(pToken);
        _tokenOffset++;

        if (pToken->syntaxKind() == SyntaxKind::EndOfFileToken)
            break;
    }

    _tokenOffset = currentTokenOffset;
}

LanguageSyntaxToken* Lexer::currentToken() noexcept
{
    switch (_mode)
    {
        case LexerMode::Syntax:
        {
            if (_tokenOffset >= _tokenCount)
                addLexedToken(lex());

            return _lexedTokens[_tokenOffset];
        }
        case LexerMode::Directive:
        {
            if (_directiveTriviaTokenOffset >= _directiveTriviaTokenCount)
                addLexedToken(lex());

            return _lexedDirectiveTriviaTokens[_directiveTriviaTokenOffset];
        }
    }

    return nullptr;
}

LanguageSyntaxToken* Lexer::takeToken(SyntaxKind syntaxKind) noexcept
{
    switch (_mode)
    {
        case LexerMode::Syntax:
        {
            _pCurrentToken = currentToken();

            if (_pCurrentToken->syntaxKind() == syntaxKind)
            {
                _tokenOffset++;
                return _pCurrentToken;
            }

            // TODO Create missing replacement token
            return nullptr;
        }
        case LexerMode::Directive:
        {
            _pCurrentDirectiveTriviaToken = currentToken();

            if (_pCurrentDirectiveTriviaToken->syntaxKind() == syntaxKind)
            {
                _directiveTriviaTokenOffset++;
                return _pCurrentDirectiveTriviaToken;
            }

            // TODO Create missing replacement token
            return nullptr;
        }
    }

    return nullptr;
}

LanguageSyntaxToken* Lexer::takeToken() noexcept
{
    switch (_mode)
    {
        case LexerMode::Syntax:
        {
            _pCurrentToken = currentToken();
            _tokenOffset++;
            return _pCurrentToken;
        }
        case LexerMode::Directive:
        {
            _pCurrentDirectiveTriviaToken = currentToken();
            _directiveTriviaTokenOffset++;
            return _pCurrentDirectiveTriviaToken;
        }
    }

    return nullptr;
}

LanguageSyntaxToken* Lexer::peekToken(pg_size n) noexcept
{
    assert(n >= 0);

    switch (_mode)
    {
        case LexerMode::Syntax:
        {
            while (_tokenOffset + n > _tokenCount)
                addLexedToken(lex());

            return _lexedTokens[_tokenOffset + n - 1];
        }
        case LexerMode::Directive:
        {
            while (_directiveTriviaTokenOffset + n > _directiveTriviaTokenCount)
                addLexedToken(lex());

            return _lexedDirectiveTriviaTokens[_directiveTriviaTokenOffset + n - 1];
        }
    }

    return nullptr;
}

void Lexer::advance() noexcept
{
    switch (_mode)
    {
        case LexerMode::Syntax:
            _tokenOffset++;
            break;
        case LexerMode::Directive:
            _directiveTriviaTokenOffset++;
            break;
    }
}

void Lexer::setMode(LexerMode mode) noexcept
{
    _lexedDirectiveTriviaTokens.clear();
    _directiveTriviaTokenCount = 0;
    _directiveTriviaTokenOffset = 0;
    _pCurrentDirectiveTriviaToken = nullptr;
    _mode = mode;
}

void Lexer::addLexedToken(LanguageSyntaxToken* token) noexcept
{
    assert(token != nullptr);

    switch (_mode)
    {
        case LexerMode::Syntax:
        {
            if (_tokenOffset >= _lexedTokens.size())
                _lexedTokens.resize(_lexedTokens.size() + 2);

            _lexedTokens[_tokenCount] = token;
            _tokenCount++;
            break;
        }
        case LexerMode::Directive:
        {
            if (_directiveTriviaTokenOffset >= _lexedDirectiveTriviaTokens.size())
                _lexedDirectiveTriviaTokens.resize(_lexedDirectiveTriviaTokens.size() + 2);

            _lexedDirectiveTriviaTokens[_directiveTriviaTokenCount] = token;
            _directiveTriviaTokenCount++;
            break;
        }
    }
}

} // end namespace polyglot::CodeAnalysis
