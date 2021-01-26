#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAXFACTORY_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAXFACTORY_H

#include <string_view>
#include <vector>
#include "polyglot/Core/Types.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxToken;
class LanguageSyntaxTrivia;
class TokenInfo;

class SyntaxFactory final
{
public:
    static LanguageSyntaxToken* token(TokenInfo& tokenInfo,
                                      pg_size position = 0) noexcept;

    static LanguageSyntaxToken* tokenWithTrivia(TokenInfo& tokenInfo,
                                                std::vector<LanguageSyntaxTrivia*>&& leadingTrivia,
                                                std::vector<LanguageSyntaxTrivia*>&& trailingTrivia,
                                                pg_size position = 0) noexcept;

    static LanguageSyntaxToken* tokenWithLeadingTrivia(TokenInfo& tokenInfo,
                                                       std::vector<LanguageSyntaxTrivia*>&& leadingTrivia,
                                                       pg_size position = 0) noexcept;

    static LanguageSyntaxToken* tokenWithTrailingTrivia(TokenInfo& tokenInfo,
                                                        std::vector<LanguageSyntaxTrivia*>&& trailingTrivia,
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
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAXFACTORY_H
