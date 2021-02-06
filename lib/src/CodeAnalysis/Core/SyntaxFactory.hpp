#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAXFACTORY_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAXFACTORY_H

#include <initializer_list>
#include <string_view>
#include <vector>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Syntax/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxList;
class LanguageSyntaxNode;
class LanguageSyntaxToken;
class LanguageSyntaxTrivia;
class SyntaxPool;
class TokenInfo;

class SyntaxFactory
{
public:
    SyntaxFactory() = delete;
    explicit SyntaxFactory(SyntaxPool& syntaxPool) noexcept;
    SyntaxFactory(const SyntaxFactory&) = delete;
    SyntaxFactory(SyntaxFactory&&) = delete;
    SyntaxFactory& operator=(const SyntaxFactory&) = delete;
    SyntaxFactory& operator=(SyntaxFactory&&) = delete;

    LanguageSyntaxToken* token(TokenInfo& tokenInfo,
                               pg_size position = 0) noexcept;

    LanguageSyntaxToken* missingToken(SyntaxKind syntaxKind,
                                      std::string_view text = "",
                                      pg_size position = 0) noexcept;

    LanguageSyntaxToken* tokenWithTrivia(TokenInfo& tokenInfo,
                                         std::vector<LanguageSyntaxNode*>&& leadingTrivia,
                                         std::vector<LanguageSyntaxNode*>&& trailingTrivia,
                                         pg_size position = 0) noexcept;

    LanguageSyntaxToken* tokenWithLeadingTrivia(TokenInfo& tokenInfo,
                                                std::vector<LanguageSyntaxNode*>&& leadingTrivia,
                                                pg_size position = 0) noexcept;

    LanguageSyntaxToken* tokenWithLeadingTrivia(SyntaxKind syntaxKind,
                                                std::string_view text,
                                                pg_size position = 0,
                                                LanguageSyntaxList* leadingTrivia = nullptr) noexcept;

    LanguageSyntaxToken* tokenWithTrailingTrivia(TokenInfo& tokenInfo,
                                                 std::vector<LanguageSyntaxNode*>&& trailingTrivia,
                                                 pg_size position = 0) noexcept;

    inline LanguageSyntaxTrivia* carriageReturnLineFeed(pg_size position = 0) noexcept { return endOfLine("\r\n", position); }
    inline LanguageSyntaxTrivia* lineFeed(pg_size position = 0) noexcept { return endOfLine("\n", position); }
    inline LanguageSyntaxTrivia* carriageReturn(pg_size position = 0) noexcept { return endOfLine("\r", position); }

    LanguageSyntaxTrivia* endOfLine(std::string_view text,
                                    pg_size position = 0) noexcept;

    LanguageSyntaxTrivia* whiteSpace(std::string_view text,
                                     pg_size position = 0) noexcept;

    LanguageSyntaxTrivia* singleLineComment(std::string_view text,
                                            pg_size position = 0) noexcept;

    LanguageSyntaxTrivia* multiLineComment(std::string_view text,
                                           pg_size position = 0) noexcept;

    LanguageSyntaxTrivia* createSyntaxTrivia(SyntaxKind syntaxKind,
                                             std::string_view text,
                                             pg_size position = 0) noexcept;

    LanguageSyntaxList* syntaxList(std::initializer_list<LanguageSyntaxNode*> syntaxNodes) noexcept;

    LanguageSyntaxNode* addSyntaxNode(UniquePtr<LanguageSyntaxNode>&& syntaxNode) noexcept;
    LanguageSyntaxToken* addSyntaxToken(UniquePtr<LanguageSyntaxToken>&& syntaxToken) noexcept;
    LanguageSyntaxTrivia* addSyntaxTrivia(UniquePtr<LanguageSyntaxTrivia>&& syntaxTrivia) noexcept;

protected:
    SyntaxPool& _syntaxPool;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAXFACTORY_H
