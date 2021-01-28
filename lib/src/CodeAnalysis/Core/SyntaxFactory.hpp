#ifndef POLYGLOT_CODEANALYSIS_CORE_PARSER_SYNTAXFACTORY_H
#define POLYGLOT_CODEANALYSIS_CORE_PARSER_SYNTAXFACTORY_H

#include <initializer_list>
#include <string_view>
#include <vector>
#include "polyglot/Core/Types.hpp"
#include "polyglot/CodeAnalysis/Core/SyntaxKinds.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxList;
class LanguageSyntaxNode;
class LanguageSyntaxToken;
class LanguageSyntaxTrivia;
class TokenInfo;

class SyntaxFactory final
{
public:
    static LanguageSyntaxToken* token(TokenInfo& tokenInfo,
                                      pg_size position = 0) noexcept;

    static LanguageSyntaxToken* tokenWithTrivia(TokenInfo& tokenInfo,
                                                std::vector<LanguageSyntaxNode*>&& leadingTrivia,
                                                std::vector<LanguageSyntaxNode*>&& trailingTrivia,
                                                pg_size position = 0) noexcept;

    static LanguageSyntaxToken* tokenWithLeadingTrivia(TokenInfo& tokenInfo,
                                                       std::vector<LanguageSyntaxNode*>&& leadingTrivia,
                                                       pg_size position = 0) noexcept;

    static LanguageSyntaxToken* tokenWithLeadingTrivia(SyntaxKind syntaxKind,
                                                       std::string_view text,
                                                       pg_size position = 0,
                                                       LanguageSyntaxList* leadingTrivia = nullptr) noexcept;

    static LanguageSyntaxToken* tokenWithTrailingTrivia(TokenInfo& tokenInfo,
                                                        std::vector<LanguageSyntaxNode*>&& trailingTrivia,
                                                        pg_size position = 0) noexcept;

    static inline LanguageSyntaxTrivia* carriageReturnLineFeed(pg_size position = 0) noexcept { return endOfLine("\r\n", position); }
    static inline LanguageSyntaxTrivia* lineFeed(pg_size position = 0) noexcept { return endOfLine("\n", position); }
    static inline LanguageSyntaxTrivia* carriageReturn(pg_size position = 0) noexcept { return endOfLine("\r", position); }

    static LanguageSyntaxTrivia* endOfLine(std::string_view text,
                                           pg_size position = 0) noexcept;

    static LanguageSyntaxTrivia* whiteSpace(std::string_view text,
                                            pg_size position = 0) noexcept;

    static LanguageSyntaxTrivia* singleLineComment(std::string_view text,
                                                   pg_size position = 0) noexcept;

    static LanguageSyntaxTrivia* multiLineComment(std::string_view text,
                                                  pg_size position = 0) noexcept;

    static LanguageSyntaxList* syntaxList(std::initializer_list<LanguageSyntaxNode*> syntaxNodes) noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_PARSER_SYNTAXFACTORY_H
