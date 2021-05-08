#ifndef POLYGLOT_DELPHI_PARSER_DELPHILEXER_H
#define POLYGLOT_DELPHI_PARSER_DELPHILEXER_H

#include <string_view>
#include "polyglot/Core/Types.hpp"
#include "Core/Syntax/SyntaxFactory.hpp"
#include "Core/Parser/Lexer.hpp"
#include "Core/Parser/TokenInfo.hpp"
#include "Core/Text/SourceText.hpp"

namespace polyglot::Delphi::Parser
{

class ISyntaxToken;
class ISyntaxTrivia;

class DelphiLexer final : public Lexer
{
public:
    explicit DelphiLexer(SharedPtr<SourceText> sourceText) noexcept;

private:
    ISyntaxToken* lexToken() noexcept override;
    TokenInfo quickScanSyntaxToken() noexcept;
    TokenInfo lexSyntaxToken() noexcept;
    TokenInfo lexSyntaxTokenLiteral(std::string_view chars) noexcept;

    void lexSyntaxTrivia(bool afterFirstToken,
                         bool isTrailing,
                         std::vector<ISyntaxTrivia*>& triviaList) noexcept;

    ISyntaxTrivia* scanWhitespace() noexcept;
    void scanToEndOfLine() noexcept;
    void scanMultiLineComment(bool& isTerminated) noexcept;
    ISyntaxTrivia* scanEndOfLine() noexcept;
    void scanSyntaxToken(TokenInfo& tokenInfo) noexcept;
    void scanStringLiteral(TokenInfo& tokenInfo) noexcept;
    void scanIdentifierOrKeyword(TokenInfo& tokenInfo) noexcept;

    void scanIdentifierOrKeyword(std::string_view chars,
                                 TokenInfo& tokenInfo) noexcept;

    bool scanIdentifier(TokenInfo& token) noexcept;
    void scanNumericLiteral(TokenInfo& tokenInfo) noexcept;

    void lexSingleDirective(bool isActive,
                            bool endIsActive,
                            bool afterFirstToken,
                            bool afterNonWhitespaceOnLine,
                            std::vector<ISyntaxTrivia*>& triviaList) noexcept;

    ISyntaxToken* lexDirectiveToken() noexcept;
    void scanDirectiveToken(TokenInfo& tokenInfo) noexcept;

    void lexDirectiveTrailingTrivia(std::vector<ISyntaxTrivia*>& triviaList,
                                    bool includeEndOfLine) noexcept;

    ISyntaxTrivia* lexDirectiveTrivia() noexcept;
    ISyntaxTrivia* scanDirectiveWhitespace() noexcept;

private:
    pg_size _currentTriviaPosition;
    SyntaxFactory _syntaxFactory;
};

} // end namespace polyglot::Delphi::Parser

#endif // POLYGLOT_DELPHI_PARSER_DELPHILEXER_H
