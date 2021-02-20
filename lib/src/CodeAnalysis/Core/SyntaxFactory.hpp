#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAXFACTORY_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAXFACTORY_H

#include <initializer_list>
#include <string_view>
#include <vector>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/SyntaxKinds.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxList.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxNode.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxToken.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxTrivia.hpp"
#include "polyglot/CodeAnalysis/Syntax/ISyntaxTriviaList.hpp"

namespace polyglot::CodeAnalysis
{

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

    ISyntaxToken* token(TokenInfo& tokenInfo,
                        pg_size position = 0) noexcept;

    ISyntaxToken* missingToken(SyntaxKind syntaxKind,
                               std::string_view text = "",
                               pg_size position = 0) noexcept;

    ISyntaxToken* tokenWithTrivia(TokenInfo& tokenInfo,
                                  std::vector<ISyntaxTrivia*>&& leadingTrivia,
                                  std::vector<ISyntaxTrivia*>&& trailingTrivia,
                                  pg_size position = 0) noexcept;

    ISyntaxToken* tokenWithLeadingTrivia(TokenInfo& tokenInfo,
                                         std::vector<ISyntaxTrivia*>&& leadingTrivia,
                                         pg_size position = 0) noexcept;

    ISyntaxToken* tokenWithLeadingTrivia(SyntaxKind syntaxKind,
                                         std::string_view text,
                                         pg_size position = 0,
                                         ISyntaxTriviaList* leadingTrivia = nullptr) noexcept;

    ISyntaxToken* tokenWithTrailingTrivia(TokenInfo& tokenInfo,
                                          std::vector<ISyntaxTrivia*>&& trailingTrivia,
                                          pg_size position = 0) noexcept;

    inline ISyntaxTrivia* carriageReturnLineFeed(pg_size position = 0) noexcept { return endOfLine("\r\n", position); }
    inline ISyntaxTrivia* lineFeed(pg_size position = 0) noexcept { return endOfLine("\n", position); }
    inline ISyntaxTrivia* carriageReturn(pg_size position = 0) noexcept { return endOfLine("\r", position); }

    ISyntaxTrivia* endOfLine(std::string_view text,
                             pg_size position = 0) noexcept;

    ISyntaxTrivia* whiteSpace(std::string_view text,
                              pg_size position = 0) noexcept;

    ISyntaxTrivia* singleLineComment(std::string_view text,
                                     pg_size position = 0) noexcept;

    ISyntaxTrivia* multiLineComment(std::string_view text,
                                    pg_size position = 0) noexcept;

    ISyntaxTrivia* createSyntaxTrivia(SyntaxKind syntaxKind,
                                      std::string_view text,
                                      pg_size position = 0) noexcept;

    ISyntaxList* syntaxList() noexcept;
    ISyntaxList* syntaxList(std::initializer_list<ISyntaxNode*> syntaxNodes) noexcept;

    ISyntaxTriviaList* syntaxTriviaList(ISyntaxToken* token = nullptr) noexcept;

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

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAXFACTORY_H
