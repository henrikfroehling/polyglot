#ifndef POLYGLOT_CODEANALYSIS_CORE_SYNTAXFACTORY_H
#define POLYGLOT_CODEANALYSIS_CORE_SYNTAXFACTORY_H

#include <string_view>
#include <vector>
#include "polyglot/Core/Types.hpp"

namespace polyglot::CodeAnalysis
{

class SyntaxToken;
class SyntaxTrivia;
class TokenInfo;

class SyntaxFactory final
{
public:
    static SyntaxToken* token(TokenInfo& tokenInfo,
                              pg_size position = 0) noexcept;

    static SyntaxToken* tokenWithTrivia(TokenInfo& tokenInfo,
                                        std::vector<SyntaxTrivia*>&& leadingTrivia,
                                        std::vector<SyntaxTrivia*>&& trailingTrivia,
                                        pg_size position = 0) noexcept;

    static SyntaxToken* tokenWithLeadingTrivia(TokenInfo& tokenInfo,
                                               std::vector<SyntaxTrivia*>&& leadingTrivia,
                                               pg_size position = 0) noexcept;

    static SyntaxToken* tokenWithTrailingTrivia(TokenInfo& tokenInfo,
                                                std::vector<SyntaxTrivia*>&& trailingTrivia,
                                                pg_size position = 0) noexcept;

    static inline SyntaxTrivia* carriageReturnLineFeed(pg_size position = 0) noexcept { return endOfLine("\r\n", position); }
    static inline SyntaxTrivia* lineFeed(pg_size position = 0) noexcept { return endOfLine("\n", position); }
    static inline SyntaxTrivia* carriageReturn(pg_size position = 0) noexcept { return endOfLine("\r", position); }

    static SyntaxTrivia* endOfLine(std::string_view text,
                                  pg_size position = 0) noexcept;

    static SyntaxTrivia* whiteSpace(std::string_view text,
                                   pg_size position = 0) noexcept;

    static SyntaxTrivia* singleLineComment(std::string_view text,
                                          pg_size position = 0) noexcept;

    static SyntaxTrivia* multiLineComment(std::string_view text,
                                         pg_size position = 0) noexcept;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_CORE_SYNTAXFACTORY_H
