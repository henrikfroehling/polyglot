#ifndef POLYGLOT_CORE_SYNTAX_SYNTAXFACTORY_H
#define POLYGLOT_CORE_SYNTAX_SYNTAXFACTORY_H

#include <initializer_list>
#include <vector>
#include "polyglot/Core/Syntax/ISyntaxList.hpp"
#include "polyglot/Core/Syntax/ISyntaxNode.hpp"
#include "polyglot/Core/Syntax/ISyntaxToken.hpp"
#include "polyglot/Core/Syntax/ISyntaxTrivia.hpp"
#include "polyglot/Core/Syntax/ISyntaxTriviaList.hpp"
#include "polyglot/Core/Syntax/SyntaxKinds.hpp"
#include "polyglot/Core/Syntax/SyntaxVariant.hpp"
#include "polyglot/Core/Types.hpp"

namespace polyglot::Core::Parser
{

class TokenInfo;

} // end namespace polyglot::Core::Parser

namespace polyglot::Core::Syntax
{

class SyntaxPool;

class SyntaxFactory
{
public:
    SyntaxFactory() = delete;
    explicit SyntaxFactory(SyntaxPool& syntaxPool) noexcept;
    SyntaxFactory(const SyntaxFactory&) = delete;
    SyntaxFactory(SyntaxFactory&&) = delete;
    SyntaxFactory& operator=(const SyntaxFactory&) = delete;
    SyntaxFactory& operator=(SyntaxFactory&&) = delete;

    ISyntaxToken* token(Parser::TokenInfo& tokenInfo,
                        pg_size position = 0) noexcept;

    ISyntaxToken* missingToken(SyntaxKind syntaxKind,
                               pg_string_view text = L"",
                               pg_size position = 0) noexcept;

    ISyntaxToken* tokenWithTrivia(Parser::TokenInfo& tokenInfo,
                                  std::vector<ISyntaxTrivia*>&& leadingTrivia,
                                  std::vector<ISyntaxTrivia*>&& trailingTrivia,
                                  pg_size position = 0) noexcept;

    ISyntaxToken* tokenWithLeadingTrivia(Parser::TokenInfo& tokenInfo,
                                         std::vector<ISyntaxTrivia*>&& leadingTrivia,
                                         pg_size position = 0) noexcept;

    ISyntaxToken* tokenWithLeadingTrivia(SyntaxKind syntaxKind,
                                         pg_string_view text,
                                         pg_size position = 0,
                                         ISyntaxTriviaList* leadingTrivia = nullptr) noexcept;

    ISyntaxToken* tokenWithTrailingTrivia(Parser::TokenInfo& tokenInfo,
                                          std::vector<ISyntaxTrivia*>&& trailingTrivia,
                                          pg_size position = 0) noexcept;

    inline ISyntaxTrivia* carriageReturnLineFeed(pg_size position = 0) noexcept { return endOfLine(L"\r\n", position); }
    inline ISyntaxTrivia* lineFeed(pg_size position = 0) noexcept { return endOfLine(L"\n", position); }
    inline ISyntaxTrivia* carriageReturn(pg_size position = 0) noexcept { return endOfLine(L"\r", position); }

    ISyntaxTrivia* endOfLine(pg_string_view text,
                             pg_size position = 0) noexcept;

    ISyntaxTrivia* whiteSpace(pg_string_view text,
                              pg_size position = 0) noexcept;

    ISyntaxTrivia* singleLineComment(pg_string_view text,
                                     pg_size position = 0) noexcept;

    ISyntaxTrivia* multiLineComment(pg_string_view text,
                                    pg_size position = 0) noexcept;

    ISyntaxTrivia* createSyntaxTrivia(SyntaxKind syntaxKind,
                                      pg_string_view text,
                                      pg_size position = 0) noexcept;

    ISyntaxList* syntaxList(SyntaxKind syntaxKind,
                            std::vector<SyntaxVariant>&& children) noexcept;

    ISyntaxTriviaList* syntaxTriviaList(std::initializer_list<ISyntaxTrivia*> trivia,
                                        ISyntaxToken* token = nullptr) noexcept;

    ISyntaxList* addSyntaxList(UniquePtr<ISyntaxList>&& syntaxList) noexcept;
    ISyntaxNode* addSyntaxNode(UniquePtr<ISyntaxNode>&& syntaxNode) noexcept;
    ISyntaxToken* addSyntaxToken(UniquePtr<ISyntaxToken>&& syntaxToken) noexcept;
    ISyntaxTrivia* addSyntaxTrivia(UniquePtr<ISyntaxTrivia>&& syntaxTrivia) noexcept;
    ISyntaxTriviaList* addSyntaxTriviaList(UniquePtr<ISyntaxTriviaList>&& syntaxTriviaList) noexcept;

protected:
    SyntaxPool& _syntaxPool;
};

} // end namespace polyglot::Core::Syntax

#endif // POLYGLOT_CORE_SYNTAX_SYNTAXFACTORY_H
