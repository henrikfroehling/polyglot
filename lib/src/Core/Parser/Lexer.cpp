#include "Lexer.hpp"
#include <cassert>
#include <algorithm>
#include "polyglot/Core/Syntax/ISyntaxNode.hpp"
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"

namespace polyglot::Core::Parser
{

using namespace polyglot::Core::Syntax;
using namespace polyglot::Core::Text;

constexpr pg_size MIN_LEXED_TOKENS_COUNT{32};
constexpr pg_size MAX_LEXED_TOKENS_COUNT{4096};

Lexer::Lexer(SharedPtr<SourceText> sourceText) noexcept
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
      _syntaxPool{},
      _syntaxFactory{_syntaxPool}
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
        ISyntaxToken* pToken = lex();
        addLexedToken(pToken);
        _tokenOffset++;

        if (pToken->syntaxKind() == SyntaxKind::EndOfFileToken)
            break;
    }

    _tokenOffset = currentTokenOffset;
}

ISyntaxToken* Lexer::currentToken() noexcept
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

ISyntaxToken* Lexer::takeToken(SyntaxKind syntaxKind) noexcept
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

            return createMissingToken(syntaxKind);
        }
        case LexerMode::Directive:
        {
            _pCurrentDirectiveTriviaToken = currentToken();

            if (_pCurrentDirectiveTriviaToken->syntaxKind() == syntaxKind)
            {
                _directiveTriviaTokenOffset++;
                return _pCurrentDirectiveTriviaToken;
            }

            return createMissingToken(syntaxKind);
        }
    }

    return nullptr;
}

ISyntaxToken* Lexer::takeToken() noexcept
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

ISyntaxToken* Lexer::peekToken(pg_size n) noexcept
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

void Lexer::addLexedToken(ISyntaxToken* token) noexcept
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

ISyntaxToken* Lexer::createMissingToken(SyntaxKind expectedSyntaxKind) noexcept
{
    return _syntaxFactory.missingToken(expectedSyntaxKind, _pCurrentToken->text(), _pCurrentToken->position());
}

} // end namespace polyglot::Core::Parser
