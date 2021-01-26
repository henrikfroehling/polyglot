#ifndef POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H
#define POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H

#include <string_view>
#include "polyglot/Core/Types.hpp"
#include "CodeAnalysis/Core/Lexer.hpp"
#include "CodeAnalysis/Core/TokenInfo.hpp"
#include "CodeAnalysis/Core/Text/SourceText.hpp"

namespace polyglot::CodeAnalysis
{

class LanguageSyntaxNode;
class LanguageSyntaxToken;
class LanguageSyntaxTrivia;
class SyntaxPool;

class DelphiLexer final : public Lexer
{
public:
    explicit DelphiLexer(SharedPtr<SourceText> sourceText,
                         SyntaxPool& syntaxPool) noexcept;

private:
    LanguageSyntaxToken* lexToken() noexcept override;
    TokenInfo quickScanSyntaxToken() noexcept;
    TokenInfo lexSyntaxToken() noexcept;
    TokenInfo lexSyntaxTokenLiteral(std::string_view chars) noexcept;

    void lexSyntaxTrivia(bool afterFirstToken,
                         bool isTrailing,
                         std::vector<LanguageSyntaxNode*>& triviaList) noexcept;

    LanguageSyntaxTrivia* scanWhitespace() noexcept;
    void scanToEndOfLine() noexcept;
    void scanMultiLineComment(bool& isTerminated) noexcept;
    LanguageSyntaxTrivia* scanEndOfLine() noexcept;
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
                            std::vector<LanguageSyntaxNode*>& triviaList) noexcept;

    LanguageSyntaxToken* lexDirectiveToken() noexcept;
    void scanDirectiveToken(TokenInfo& tokenInfo) noexcept;

    void lexDirectiveTrailingTrivia(std::vector<LanguageSyntaxNode*>& triviaList,
                                    bool includeEndOfLine) noexcept;

    LanguageSyntaxTrivia* lexDirectiveTrivia() noexcept;
    LanguageSyntaxTrivia* scanDirectiveWhitespace() noexcept;

private:
    pg_size _currentTriviaPosition;
};

} // end namespace polyglot::CodeAnalysis

#endif // POLYGLOT_CODEANALYSIS_DELPHI_DELPHILEXER_H
